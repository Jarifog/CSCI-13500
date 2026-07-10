"""
================================================================================
S&P 500 BULLISH STOCK SCREENER
================================================================================
Finds the top 10 S&P 500 stocks with the highest probability of an upside move
intraday or within the next few trading days, using:
  - Oversold technical indicators
  - Bullish reversal/bounce signals
  - Bullish options/gamma-related indicators
  - Historical upside response after similar setups

INSTALL:
    pip install yfinance pandas numpy pandas_ta requests beautifulsoup4 tabulate scipy

USAGE:
    python sp500_bullish_screener.py

OUTPUT:
    - Printed ranked top-10 table
    - CSV: sp500_bullish_screener_results.csv
================================================================================
"""

# ── Standard library ──────────────────────────────────────────────────────────
import warnings
import time
import os
import sys
from datetime import datetime, timedelta

warnings.filterwarnings("ignore")

# ── Third-party ───────────────────────────────────────────────────────────────
try:
    import yfinance as yf
    import pandas as pd
    import numpy as np
    import pandas_ta as ta
    import requests
    from bs4 import BeautifulSoup
    from tabulate import tabulate
    from scipy.stats import percentileofscore
except ImportError as e:
    sys.exit(
        f"\n[ERROR] Missing library: {e}\n"
        "Run:  pip install yfinance pandas numpy pandas_ta requests beautifulsoup4 tabulate scipy\n"
    )

# ==============================================================================
#  CONFIG  ─ edit thresholds here
# ==============================================================================
CONFIG = {
    # ── Screening thresholds ──────────────────────────────────────────────────
    "rsi_oversold":            40,    # RSI below this is considered oversold
    "rsi_deeply_oversold":     30,    # Extra reward below this
    "stoch_rsi_oversold":      25,    # StochRSI %K below this
    "bb_pct_oversold":         0.20,  # BB %B below this (0 = lower band, 1 = upper)
    "pullback_days":           5,     # Days to measure short-term pullback
    "atr_period":              14,

    # ── Scoring weights ────────────────────────────────────────────────────────
    "weight_oversold":         0.25,
    "weight_reversal":         0.30,
    "weight_options":          0.25,
    "weight_historical":       0.20,

    # ── Stage 1 top-N to carry into Stage 2 ───────────────────────────────────
    "stage1_top_n":            20,    # Broader pool before deep review
    "final_top_n":             10,

    # ── Data settings ─────────────────────────────────────────────────────────
    "hist_period":             "1y",   # Price history for indicator calc
    "hist_lookback_days":      252,    # Trading days for historical analysis
    "options_max_strikes":     20,     # Max OI strikes to scan per expiry
    "request_delay":           0.15,   # Seconds between yfinance calls
    "output_csv":              "sp500_bullish_screener_results.csv",
}

# ==============================================================================
#  UNIVERSE  ─ fetch S&P 500 tickers from Wikipedia
# ==============================================================================

def get_sp500_tickers() -> list[str]:
    """Scrape the current S&P 500 constituent list from Wikipedia."""
    url = "https://en.wikipedia.org/wiki/List_of_S%26P_500_companies"
    try:
        headers = {"User-Agent": "Mozilla/5.0 (compatible; SP500Screener/1.0)"}
        resp = requests.get(url, timeout=15, headers=headers)
        soup = BeautifulSoup(resp.text, "html.parser")
        table = soup.find("table", {"id": "constituents"})
        tickers = [
            row.find_all("td")[0].text.strip().replace(".", "-")
            for row in table.find_all("tr")[1:]
        ]
        print(f"[INFO] Fetched {len(tickers)} S&P 500 tickers from Wikipedia.")
        return tickers
    except Exception as exc:
        print(f"[WARN] Wikipedia fetch failed ({exc}). Using hardcoded subset.")
        # Fallback: small representative set
        return [
            "AAPL","MSFT","NVDA","AMZN","META","GOOGL","TSLA","JPM","UNH","V",
            "XOM","LLY","JNJ","WMT","MA","PG","HD","MRK","AVGO","CVX",
            "ABBV","COST","PEP","KO","ADBE","CRM","ACN","AMD","CSCO","TMO",
            "ABT","MCD","BAC","NKE","INTC","WFC","DHR","VZ","CMCSA","NFLX",
            "DIS","PM","TXN","ORCL","NEE","BMY","UPS","RTX","AMGN","HON",
        ]

# ==============================================================================
#  DATA FETCHING
# ==============================================================================

def fetch_price_history(ticker: str) -> pd.DataFrame | None:
    """Download OHLCV history; return None on failure."""
    try:
        df = yf.download(ticker, period=CONFIG["hist_period"],
                         interval="1d", progress=False, auto_adjust=True)
        if df is None or len(df) < 60:
            return None
        df.columns = [c[0] if isinstance(c, tuple) else c for c in df.columns]
        return df
    except Exception:
        return None


def fetch_options_data(ticker: str) -> dict:
    """
    Pull options chain for the nearest 1–2 expirations.
    Returns aggregated call/put volume, OI, put-call ratio, walls, gamma bias.
    """
    result = {
        "call_vol": 0, "put_vol": 0,
        "call_oi":  0, "put_oi":  0,
        "pcr_vol":  1.0, "pcr_oi": 1.0,
        "call_wall": None, "put_wall": None,
        "gamma_bias": 0.0,
        "max_pain":   None,
    }
    try:
        tk = yf.Ticker(ticker)
        exps = tk.options
        if not exps:
            return result

        current_price = tk.fast_info.get("lastPrice") or tk.fast_info.get("last_price")
        if not current_price:
            hist = tk.history(period="2d")
            if hist.empty:
                return result
            current_price = float(hist["Close"].iloc[-1])

        # Use first 2 expirations for better coverage
        target_exps = exps[:2]
        all_calls, all_puts = [], []

        for exp in target_exps:
            chain = tk.option_chain(exp)
            calls = chain.calls.copy()
            puts  = chain.puts.copy()

            # Days to expiration weight (closer = more influence)
            exp_dt  = datetime.strptime(exp, "%Y-%m-%d")
            dte     = max((exp_dt - datetime.now()).days, 1)
            dte_wt  = 1 / dte  # nearer expiry = higher weight

            calls["dte_wt"] = dte_wt
            puts["dte_wt"]  = dte_wt
            all_calls.append(calls)
            all_puts.append(puts)

        calls_df = pd.concat(all_calls).reset_index(drop=True) if all_calls else pd.DataFrame()
        puts_df  = pd.concat(all_puts).reset_index(drop=True) if all_puts else pd.DataFrame()

        if calls_df.empty and puts_df.empty:
            return result

        # Totals
        result["call_vol"] = int(calls_df["volume"].fillna(0).sum())
        result["put_vol"]  = int(puts_df["volume"].fillna(0).sum())
        result["call_oi"]  = int(calls_df["openInterest"].fillna(0).sum())
        result["put_oi"]   = int(puts_df["openInterest"].fillna(0).sum())

        # Put/call ratios
        result["pcr_vol"] = round(
            result["put_vol"]  / result["call_vol"]  if result["call_vol"]  > 0 else 9.9, 2)
        result["pcr_oi"]  = round(
            result["put_oi"]   / result["call_oi"]   if result["call_oi"]   > 0 else 9.9, 2)

        # ── Gamma-bias approximation ───────────────────────────────────────────
        # Proxy: OI-weighted moneyness of calls vs puts relative to spot.
        # Positive = net call pressure above spot (bullish / upward dealer hedging)
        # Negative = net put pressure below spot (bearish / downward dealer hedging)
        def gamma_score(df, is_call):
            if df.empty:
                return 0.0
            df = df.copy()
            df["strike"]       = pd.to_numeric(df["strike"],       errors="coerce")
            df["openInterest"] = pd.to_numeric(df["openInterest"], errors="coerce").fillna(0)
            df["dte_wt"]       = df["dte_wt"].fillna(1)
            df["dist"]         = df["strike"] - current_price
            # Normalize distance; strikes very far away carry less weight
            df["dist_wt"]      = np.exp(-abs(df["dist"]) / (current_price * 0.05))
            df["raw"]          = df["openInterest"] * df["dte_wt"] * df["dist_wt"]
            total = df["raw"].sum()
            if total == 0:
                return 0.0
            # For calls above spot: positive score; for puts below spot: negative
            if is_call:
                above = df.loc[df["strike"] > current_price, "raw"].sum()
                return above / total
            else:
                below = df.loc[df["strike"] < current_price, "raw"].sum()
                return -(below / total)

        gamma_c = gamma_score(calls_df, is_call=True)
        gamma_p = gamma_score(puts_df,  is_call=False)
        result["gamma_bias"] = round(gamma_c + gamma_p, 4)

        # ── Call wall (highest OI call strike above spot) ──────────────────────
        calls_above = calls_df[calls_df["strike"] > current_price].copy() if not calls_df.empty else pd.DataFrame()
        if not calls_above.empty:
            result["call_wall"] = float(
                calls_above.sort_values("openInterest", ascending=False)["strike"].iloc[0])

        # ── Put wall (highest OI put strike below spot) ────────────────────────
        puts_below = puts_df[puts_df["strike"] < current_price].copy() if not puts_df.empty else pd.DataFrame()
        if not puts_below.empty:
            result["put_wall"] = float(
                puts_below.sort_values("openInterest", ascending=False)["strike"].iloc[0])

        # ── Max pain (strike where total OI loss is minimized) ────────────────
        try:
            strikes = sorted(set(
                calls_df["strike"].dropna().tolist() +
                puts_df["strike"].dropna().tolist()
            ))
            pain = {}
            for s in strikes:
                c_pain = calls_df.apply(
                    lambda r: max(0, s - r["strike"]) * r["openInterest"], axis=1).sum()
                p_pain = puts_df.apply(
                    lambda r: max(0, r["strike"] - s) * r["openInterest"], axis=1).sum()
                pain[s] = c_pain + p_pain
            result["max_pain"] = min(pain, key=pain.get)
        except Exception:
            pass

    except Exception:
        pass

    return result

# ==============================================================================
#  TECHNICAL INDICATORS
# ==============================================================================

def compute_indicators(df: pd.DataFrame, ticker: str) -> dict | None:
    """
    Compute all technical indicators needed for scoring.
    Returns a flat dict of indicator values or None if data insufficient.
    """
    try:
        close = df["Close"].astype(float)
        high  = df["High"].astype(float)
        low   = df["Low"].astype(float)
        vol   = df["Volume"].astype(float)

        # ── RSI(14) ────────────────────────────────────────────────────────────
        rsi_series = ta.rsi(close, length=14)
        rsi = float(rsi_series.iloc[-1]) if rsi_series is not None else 50.0

        # ── Stochastic RSI ─────────────────────────────────────────────────────
        stoch = ta.stochrsi(close, length=14, rsi_length=14, k=3, d=3)
        stoch_k = float(stoch["STOCHRSIk_14_14_3_3"].iloc[-1]) if stoch is not None else 50.0
        stoch_d = float(stoch["STOCHRSId_14_14_3_3"].iloc[-1]) if stoch is not None else 50.0

        # ── Bollinger Bands ────────────────────────────────────────────────────
        bb = ta.bbands(close, length=20, std=2)
        price_now = float(close.iloc[-1])
        if bb is not None:
            col_lower = next((c for c in bb.columns if c.startswith("BBL")), None)
            col_upper = next((c for c in bb.columns if c.startswith("BBU")), None)
            bb_lower  = float(bb[col_lower].iloc[-1]) if col_lower else price_now
            bb_upper  = float(bb[col_upper].iloc[-1]) if col_upper else price_now
        else:
            bb_lower, bb_upper = price_now, price_now
        bb_dist_pct = (price_now - bb_lower) / (bb_upper - bb_lower + 1e-9)

        # ── Moving averages ────────────────────────────────────────────────────
        ema9  = float(ta.ema(close, length=9).iloc[-1])
        ema20 = float(ta.ema(close, length=20).iloc[-1])
        sma50 = float(ta.sma(close, length=50).iloc[-1])
        sma200= float(ta.sma(close, length=200).iloc[-1]) if len(close) >= 200 else float(close.mean())

        dist_ema9   = (price_now - ema9)   / ema9   * 100
        dist_ema20  = (price_now - ema20)  / ema20  * 100
        dist_sma50  = (price_now - sma50)  / sma50  * 100
        dist_sma200 = (price_now - sma200) / sma200 * 100

        # ── ATR(14) ────────────────────────────────────────────────────────────
        atr_series = ta.atr(high, low, close, length=CONFIG["atr_period"])
        atr = float(atr_series.iloc[-1]) if atr_series is not None else 0.0
        atr_pct = atr / price_now * 100

        # ── Pullback strength (3-day, 5-day) ──────────────────────────────────
        ret_3d = (price_now / float(close.iloc[-4]) - 1) * 100 if len(close) >= 4 else 0.0
        ret_5d = (price_now / float(close.iloc[-6]) - 1) * 100 if len(close) >= 6 else 0.0

        # ── Rate of change ─────────────────────────────────────────────────────
        roc = float(ta.roc(close, length=5).iloc[-1]) if ta.roc(close, length=5) is not None else 0.0

        # ── Relative volume ────────────────────────────────────────────────────
        avg_vol_20 = float(vol.rolling(20).mean().iloc[-1])
        rel_vol    = float(vol.iloc[-1]) / avg_vol_20 if avg_vol_20 > 0 else 1.0

        # ── MACD ───────────────────────────────────────────────────────────────
        macd = ta.macd(close, fast=12, slow=26, signal=9)
        macd_line  = float(macd["MACD_12_26_9"].iloc[-1])  if macd is not None else 0.0
        macd_hist  = float(macd["MACDh_12_26_9"].iloc[-1]) if macd is not None else 0.0
        macd_hist_prev = float(macd["MACDh_12_26_9"].iloc[-2]) if macd is not None else 0.0

        # ── Candle structure (last candle) ─────────────────────────────────────
        o  = float(df["Open"].iloc[-1])
        h  = float(high.iloc[-1])
        l  = float(low.iloc[-1])
        c  = float(close.iloc[-1])
        body       = abs(c - o)
        lower_wick = min(o, c) - l
        upper_wick = h - max(o, c)
        total_rng  = h - l + 1e-9
        lower_wick_ratio = lower_wick / total_rng
        is_hammer        = (lower_wick_ratio > 0.55) and (body / total_rng < 0.45)
        is_bullish_engulf = (c > o) and (float(close.iloc[-2]) < float(df["Open"].iloc[-2]))  # simple check

        # ── Volume spike (capitulation proxy) ─────────────────────────────────
        vol_spike = rel_vol > 1.8 and ret_5d < -3.0  # high volume on a down move

        return {
            "price":             round(price_now, 2),
            "rsi":               round(rsi, 1),
            "stoch_k":           round(stoch_k, 1),
            "stoch_d":           round(stoch_d, 1),
            "bb_pct":            round(bb_dist_pct, 3),
            "bb_lower":          round(bb_lower, 2),
            "bb_upper":          round(bb_upper, 2),
            "dist_ema9":         round(dist_ema9, 2),
            "dist_ema20":        round(dist_ema20, 2),
            "dist_sma50":        round(dist_sma50, 2),
            "dist_sma200":       round(dist_sma200, 2),
            "atr":               round(atr, 2),
            "atr_pct":           round(atr_pct, 2),
            "ret_3d":            round(ret_3d, 2),
            "ret_5d":            round(ret_5d, 2),
            "roc":               round(roc, 2),
            "rel_vol":           round(rel_vol, 2),
            "macd_hist":         round(macd_hist, 4),
            "macd_hist_prev":    round(macd_hist_prev, 4),
            "lower_wick_ratio":  round(lower_wick_ratio, 3),
            "is_hammer":         is_hammer,
            "is_bullish_engulf": is_bullish_engulf,
            "vol_spike":         vol_spike,
            "ema9":              round(ema9, 2),
            "ema20":             round(ema20, 2),
            "sma50":             round(sma50, 2),
            "sma200":            round(sma200, 2),
            # raw close needed for historical analysis
            "_close_series":     close,
        }
    except Exception as exc:
        print(f"  [WARN] Indicator error for {ticker}: {exc}")
        return None

# ==============================================================================
#  HISTORICAL UPSIDE ANALYSIS
# ==============================================================================

def historical_upside_analysis(close: pd.Series, rsi_threshold: float = 40.0) -> dict:
    """
    Find past instances where RSI was below `rsi_threshold` (oversold)
    and measure forward returns at 1, 3, 5 days.
    Returns win rates and average returns for upside (bullish) analysis.
    """
    results = {"win1": 0, "win3": 0, "win5": 0,
               "avg1": 0, "avg3": 0, "avg5": 0,
               "n_samples": 0}
    try:
        rsi_s = ta.rsi(close, length=14).dropna()
        fwd1, fwd3, fwd5 = [], [], []

        for i in range(len(rsi_s) - 6):
            if rsi_s.iloc[i] < rsi_threshold:
                base = close.iloc[i]
                r1   = (close.iloc[i + 1] / base - 1) * 100
                r3   = (close.iloc[i + 3] / base - 1) * 100
                r5   = (close.iloc[i + 5] / base - 1) * 100
                fwd1.append(r1); fwd3.append(r3); fwd5.append(r5)

        n = len(fwd1)
        if n == 0:
            return results

        results["n_samples"] = n
        results["win1"]  = round(sum(r > 0 for r in fwd1) / n * 100, 1)
        results["win3"]  = round(sum(r > 0 for r in fwd3) / n * 100, 1)
        results["win5"]  = round(sum(r > 0 for r in fwd5) / n * 100, 1)
        results["avg1"]  = round(np.mean(fwd1), 2)
        results["avg3"]  = round(np.mean(fwd3), 2)
        results["avg5"]  = round(np.mean(fwd5), 2)
    except Exception:
        pass
    return results

# ==============================================================================
#  SCORING ENGINE
# ==============================================================================

def score_oversold(ind: dict) -> float:
    """
    Score 0-100 based on how oversold the stock is.
    Higher = more oversold. Purely quantifies oversold depth.
    """
    score = 0.0

    # RSI (max 30)
    if ind["rsi"] < CONFIG["rsi_deeply_oversold"]:
        score += 30
    elif ind["rsi"] < CONFIG["rsi_oversold"]:
        score += 10 + (CONFIG["rsi_oversold"] - ind["rsi"]) / (CONFIG["rsi_oversold"] - CONFIG["rsi_deeply_oversold"]) * 20

    # Stochastic RSI (max 20)
    if ind["stoch_k"] < CONFIG["stoch_rsi_oversold"]:
        score += 10 + (CONFIG["stoch_rsi_oversold"] - ind["stoch_k"]) / CONFIG["stoch_rsi_oversold"] * 10

    # BB distance from lower band (max 20)
    if ind["bb_pct"] < CONFIG["bb_pct_oversold"]:
        score += (1 - ind["bb_pct"] / CONFIG["bb_pct_oversold"]) * 20

    # Pullback magnitude (max 15)
    if ind["ret_5d"] < -5:
        score += 15
    elif ind["ret_5d"] < -3:
        score += 8
    elif ind["ret_5d"] < -1:
        score += 3

    # Distance below EMA20 (max 15)
    if ind["dist_ema20"] < -5:
        score += 15
    elif ind["dist_ema20"] < -3:
        score += 8
    elif ind["dist_ema20"] < -1:
        score += 3

    return min(score, 100.0)


def score_bullish_reversal(ind: dict) -> float:
    """
    Score 0-100 for bullish reversal / bounce confirmation signals.
    This is the CONFIRMATION layer – oversold alone is not enough.
    """
    score = 0.0

    # MACD histogram turning positive (divergence proxy) (max 20)
    if ind["macd_hist"] > 0 and ind["macd_hist_prev"] < 0:
        score += 20  # fresh bullish crossover
    elif ind["macd_hist"] > ind["macd_hist_prev"] and ind["macd_hist"] < 0:
        score += 10  # histogram curling up (still negative but improving)

    # Hammer candle (max 20)
    if ind["is_hammer"]:
        score += 20
    elif ind["lower_wick_ratio"] > 0.40:
        score += 10

    # Bullish engulfing (max 15)
    if ind["is_bullish_engulf"]:
        score += 15

    # Volume spike on down move followed by stabilization (max 15)
    if ind["vol_spike"]:
        score += 10  # capitulation signal

    # Relative volume elevated (interest returning) (max 10)
    if ind["rel_vol"] > 1.5:
        score += 10
    elif ind["rel_vol"] > 1.2:
        score += 5

    # Price recovering above EMA9 (mean-reversion signal) (max 10)
    if ind["price"] > ind["ema9"] and ind["dist_ema20"] < -1:
        score += 10  # bounced above short EMA while still below 20EMA

    # RSI divergence proxy: RSI is oversold but ROC is improving (max 10)
    if ind["rsi"] < CONFIG["rsi_oversold"] and ind["roc"] > 0:
        score += 10

    return min(score, 100.0)


def score_options(opt: dict, price: float) -> float:
    """
    Score 0-100 for bullish options/gamma setup.
    Rewards low put/call ratio, supportive put wall, call-heavy OI, positive gamma bias.
    """
    score = 0.0

    # Put/call ratio by volume (max 25)  ─ lower is more bullish
    pcr = opt["pcr_vol"]
    if pcr < 0.5:
        score += 25
    elif pcr < 0.8:
        score += 15
    elif pcr < 1.0:
        score += 8
    elif pcr > 1.5:
        score -= 10  # bearish leaning, penalize

    # Put/call ratio by OI (max 20)
    pcr_oi = opt["pcr_oi"]
    if pcr_oi < 0.5:
        score += 20
    elif pcr_oi < 0.8:
        score += 12
    elif pcr_oi < 1.0:
        score += 5
    elif pcr_oi > 1.5:
        score -= 8

    # Gamma bias (max 25)  ─ positive = net call pressure, bullish
    gb = opt["gamma_bias"]
    if gb > 0.3:
        score += 25
    elif gb > 0.15:
        score += 15
    elif gb > 0.0:
        score += 8
    elif gb < -0.15:
        score -= 10

    # Put wall support (max 15)  ─ put wall close below price = dealer support floor
    if opt["put_wall"] and price > 0:
        put_dist_pct = (price - opt["put_wall"]) / price * 100
        if 0 < put_dist_pct < 2:
            score += 15  # very close put wall = strong support
        elif put_dist_pct < 5:
            score += 8

    # Call wall proximity (max 15)  ─ call wall not too far = room to rally toward it
    if opt["call_wall"] and price > 0:
        call_dist_pct = (opt["call_wall"] - price) / price * 100
        if 0 < call_dist_pct < 3:
            score += 15  # nearby call wall = potential squeeze target
        elif call_dist_pct < 6:
            score += 8

    # Max pain above current price = bullish (max 10)
    if opt["max_pain"] and price > 0:
        if opt["max_pain"] > price:
            score += 10

    return min(max(score, 0), 100.0)


def score_historical(hist: dict) -> float:
    """
    Score 0-100 based on historical upside response to similar oversold setups.
    """
    score = 0.0
    if hist["n_samples"] < 5:
        return 50.0  # neutral when insufficient data

    # Win rate at 3 days (max 40)
    score += min(hist["win3"] * 0.4, 40)

    # Average 3-day return (max 30)
    score += min(max(hist["avg3"] * 5, 0), 30)  # +1% avg = 5pts, capped at 30

    # Win rate at 5 days (max 20)
    score += min(hist["win5"] * 0.2, 20)

    # Consistency bonus: win1 also high (max 10)
    if hist["win1"] > 60:
        score += 10

    return min(score, 100.0)


def composite_score(os_: float, rev_: float, opt_: float, hist_: float) -> float:
    """Weighted composite score. Returns 0-100."""
    w = CONFIG
    return round(
        w["weight_oversold"]   * os_   +
        w["weight_reversal"]   * rev_  +
        w["weight_options"]    * opt_  +
        w["weight_historical"] * hist_,
        2,
    )

# ==============================================================================
#  PLAIN-ENGLISH REASON BUILDER
# ==============================================================================

def build_reason(ind: dict, opt: dict, hist: dict,
                 os_: float, rev_: float, opt_score: float,
                 hs: float) -> str:
    parts = []

    # Oversold depth
    if ind["rsi"] < 30:
        parts.append("deeply oversold (RSI <30)")
    elif ind["rsi"] < 40:
        parts.append("oversold (RSI <40)")

    # Reversal signals
    if ind["is_hammer"]:
        parts.append("hammer/rejection candle")
    if ind["is_bullish_engulf"]:
        parts.append("bullish engulfing candle")
    if ind["macd_hist"] > 0 and ind["macd_hist_prev"] < 0:
        parts.append("fresh MACD bullish crossover")
    elif ind["macd_hist"] > ind["macd_hist_prev"]:
        parts.append("MACD histogram curling up")
    if ind["vol_spike"]:
        parts.append("capitulation volume spike")

    # Options
    if opt["pcr_vol"] < 0.7:
        parts.append(f"bullish call-heavy options (PCR vol {opt['pcr_vol']})")
    if opt["gamma_bias"] > 0.15:
        parts.append(f"positive gamma bias ({opt['gamma_bias']})")
    if opt["put_wall"] and opt["put_wall"] < ind["price"]:
        parts.append(f"put wall support near ${opt['put_wall']:.0f}")
    if opt["call_wall"] and opt["call_wall"] > ind["price"]:
        parts.append(f"call wall target at ${opt['call_wall']:.0f}")

    # Historical
    if hist["n_samples"] >= 5:
        parts.append(
            f"historical 3d win rate {hist['win3']}% "
            f"(avg +{hist['avg3']}% over {hist['n_samples']} samples)"
        )

    return "; ".join(parts) if parts else "Oversold with limited confirmation"


def intraday_vs_multiday(ind: dict, opt: dict, hist: dict) -> str:
    """Rough heuristic for whether setup favors same-day or multi-day upside."""
    intraday_pts   = 0
    multiday_pts   = 0

    # Hammer + high rel vol = intraday bounce likely
    if ind["is_hammer"]:           intraday_pts  += 2
    if ind["rel_vol"] > 1.5:       intraday_pts  += 2
    if opt["pcr_vol"] < 0.6:       intraday_pts  += 1

    # MACD cross + historical = multi-day follow through
    if ind["macd_hist"] > 0 and ind["macd_hist_prev"] < 0:
        multiday_pts += 3
    if hist["win5"] > 60:          multiday_pts  += 2
    if hist["avg5"] > 1.0:         multiday_pts  += 1
    if opt["gamma_bias"] > 0.2:    multiday_pts  += 1

    if intraday_pts >= multiday_pts:
        return "Same-day / intraday"
    return "Multi-day (1–5 days)"

# ==============================================================================
#  STAGE 1 ─ BROAD SCAN
# ==============================================================================

def stage1_scan(tickers: list[str]) -> list[dict]:
    """
    Scan all tickers, compute scores, return sorted list of candidate dicts.
    """
    results = []
    total   = len(tickers)

    for idx, ticker in enumerate(tickers, 1):
        print(f"  [{idx:>3}/{total}] {ticker:<6}", end="\r")
        time.sleep(CONFIG["request_delay"])

        df = fetch_price_history(ticker)
        if df is None:
            continue

        ind = compute_indicators(df, ticker)
        if ind is None:
            continue

        # Quick pre-filter: must be at least a little oversold
        if ind["rsi"] > 55 and ind["stoch_k"] > 45:
            continue

        close_s = ind.pop("_close_series")

        opt  = fetch_options_data(ticker)
        hist = historical_upside_analysis(close_s, rsi_threshold=CONFIG["rsi_oversold"])

        os_  = score_oversold(ind)
        rev_ = score_bullish_reversal(ind)
        opt_ = score_options(opt, ind["price"])
        hs   = score_historical(hist)
        comp = composite_score(os_, rev_, opt_, hs)

        # Only include stocks where reversal + options score suggest bullish bias
        if rev_ < 10 and opt_ < 15:
            continue  # no confirmation; skip

        reason = build_reason(ind, opt, hist, os_, rev_, opt_, hs)
        timing = intraday_vs_multiday(ind, opt, hist)

        row = {
            "ticker":           ticker,
            "price":            ind["price"],
            "rsi":              ind["rsi"],
            "stoch_k":          ind["stoch_k"],
            "bb_pct":           ind["bb_pct"],
            "dist_ema9":        ind["dist_ema9"],
            "dist_ema20":       ind["dist_ema20"],
            "dist_sma50":       ind["dist_sma50"],
            "atr":              ind["atr"],
            "atr_pct":          ind["atr_pct"],
            "rel_vol":          ind["rel_vol"],
            "ret_3d":           ind["ret_3d"],
            "ret_5d":           ind["ret_5d"],
            "call_vol":         opt["call_vol"],
            "put_vol":          opt["put_vol"],
            "call_oi":          opt["call_oi"],
            "put_oi":           opt["put_oi"],
            "pcr_vol":          opt["pcr_vol"],
            "pcr_oi":           opt["pcr_oi"],
            "call_wall":        opt["call_wall"],
            "put_wall":         opt["put_wall"],
            "gamma_bias":       opt["gamma_bias"],
            "max_pain":         opt["max_pain"],
            "oversold_score":   round(os_, 1),
            "reversal_score":   round(rev_, 1),
            "options_score":    round(opt_, 1),
            "hist_score":       round(hs, 1),
            "composite_score":  comp,
            "hist_win1":        hist["win1"],
            "hist_win3":        hist["win3"],
            "hist_win5":        hist["win5"],
            "hist_avg1":        hist["avg1"],
            "hist_avg3":        hist["avg3"],
            "hist_avg5":        hist["avg5"],
            "hist_samples":     hist["n_samples"],
            "reason":           reason,
            "timing":           timing,
        }
        results.append(row)

    results.sort(key=lambda x: x["composite_score"], reverse=True)
    print()
    return results

# ==============================================================================
#  STAGE 2 ─ DEEP REVIEW OF TOP N
# ==============================================================================

def stage2_deep_review(candidates: list[dict]) -> list[dict]:
    """
    Perform a deeper second-pass analysis on Stage 1 top-N.
    Re-weights scores using additional detail checks.
    """
    print(f"\n[Stage 2] Deep review of top {len(candidates)} candidates...")
    reviewed = []

    for row in candidates:
        ticker = row["ticker"]
        time.sleep(CONFIG["request_delay"])

        # Re-download to get fresh data + a longer window
        try:
            df_long = yf.download(ticker, period="2y", interval="1d",
                                  progress=False, auto_adjust=True)
            df_long.columns = [c[0] if isinstance(c, tuple) else c for c in df_long.columns]
        except Exception:
            df_long = None

        adj = 1.0  # adjustment multiplier for composite score

        if df_long is not None and len(df_long) >= 60:
            close_l = df_long["Close"].astype(float)

            # ── Support/resistance check ───────────────────────────────────────
            # Is price near a 52-week low (strong support zone)?
            low_52w = float(close_l.tail(252).min())
            price   = row["price"]
            dist_from_52w_low = (price - low_52w) / low_52w * 100
            if dist_from_52w_low < 5:
                adj *= 1.10  # near annual support → bonus
                row["reason"] += "; near 52-week low support"

            # ── Candle detail: last 5 candles ──────────────────────────────────
            recent = df_long.tail(5)
            bullish_closes = (recent["Close"] > recent["Open"]).sum()
            if bullish_closes >= 3:
                adj *= 1.05  # majority bullish closes recently

            # ── Volume trend ───────────────────────────────────────────────────
            avg_vol    = float(df_long["Volume"].tail(20).mean())
            recent_vol = float(df_long["Volume"].tail(3).mean())
            if recent_vol > avg_vol * 1.3:
                adj *= 1.05  # volume increasing, interest returning

            # ── Re-run historical with 2-year data ────────────────────────────
            hist2 = historical_upside_analysis(close_l, rsi_threshold=CONFIG["rsi_oversold"])
            if hist2["n_samples"] > row["hist_samples"]:
                new_hs = score_historical(hist2)
                row["hist_score"]  = round(new_hs, 1)
                row["hist_win1"]   = hist2["win1"]
                row["hist_win3"]   = hist2["win3"]
                row["hist_win5"]   = hist2["win5"]
                row["hist_avg1"]   = hist2["avg1"]
                row["hist_avg3"]   = hist2["avg3"]
                row["hist_avg5"]   = hist2["avg5"]
                row["hist_samples"]= hist2["n_samples"]

        # ── Options re-check ──────────────────────────────────────────────────
        opt2 = fetch_options_data(ticker)
        if opt2["call_oi"] + opt2["put_oi"] > 0:
            new_opt_score = score_options(opt2, row["price"])
            row["options_score"]  = round(new_opt_score, 1)
            row["gamma_bias"]     = opt2["gamma_bias"]
            row["pcr_vol"]        = opt2["pcr_vol"]
            row["pcr_oi"]         = opt2["pcr_oi"]
            row["call_wall"]      = opt2["call_wall"]
            row["put_wall"]       = opt2["put_wall"]

        # Recompute composite after Stage 2 adjustments
        new_comp = composite_score(
            row["oversold_score"], row["reversal_score"],
            row["options_score"],  row["hist_score"]
        ) * adj
        row["composite_score"] = round(new_comp, 2)
        row["stage2_adj"]      = round(adj, 3)

        reviewed.append(row)

    reviewed.sort(key=lambda x: x["composite_score"], reverse=True)
    return reviewed[:CONFIG["final_top_n"]]

# ==============================================================================
#  OUTPUT
# ==============================================================================

def print_ranked_table(top10: list[dict]) -> None:
    print("\n" + "=" * 100)
    print(f"  TOP {len(top10)} BULLISH BOUNCE CANDIDATES  ─  {datetime.now().strftime('%Y-%m-%d %H:%M')}")
    print("=" * 100)

    table_rows = []
    for rank, row in enumerate(top10, 1):
        table_rows.append([
            rank,
            row["ticker"],
            f"${row['price']:.2f}",
            row["rsi"],
            row["stoch_k"],
            f"{row['bb_pct']:.2f}",
            row["pcr_vol"],
            f"{row['gamma_bias']:+.3f}",
            row["oversold_score"],
            row["reversal_score"],
            row["options_score"],
            row["hist_score"],
            row["composite_score"],
            row["timing"],
        ])

    headers = [
        "#", "Ticker", "Price", "RSI", "StochK", "BB%",
        "PCR", "GammaBias", "OvSld", "Revrs", "Opts", "Hist",
        "SCORE", "Timing"
    ]
    print(tabulate(table_rows, headers=headers, tablefmt="rounded_outline",
                   numalign="right", stralign="left"))


def print_detail_cards(top10: list[dict]) -> None:
    print("\n" + "=" * 100)
    print("  DETAIL CARDS")
    print("=" * 100)
    for rank, row in enumerate(top10, 1):
        print(f"\n{'─'*80}")
        print(f"  #{rank}  {row['ticker']}  |  Price: ${row['price']:.2f}  |  Score: {row['composite_score']}")
        print(f"{'─'*80}")
        print(f"  RSI: {row['rsi']}   StochK: {row['stoch_k']}   BB%: {row['bb_pct']:.2f}   ATR: {row['atr']:.2f} ({row['atr_pct']:.1f}%)")
        print(f"  Dist EMA9: {row['dist_ema9']:+.1f}%   EMA20: {row['dist_ema20']:+.1f}%   SMA50: {row['dist_sma50']:+.1f}%")
        print(f"  3d Ret: {row['ret_3d']:+.1f}%   5d Ret: {row['ret_5d']:+.1f}%   RelVol: {row['rel_vol']:.1f}x")
        print(f"  Options: Call Vol {row['call_vol']:,} | Put Vol {row['put_vol']:,} | PCR Vol: {row['pcr_vol']}  PCR OI: {row['pcr_oi']}")
        print(f"           Call OI {row['call_oi']:,} | Put OI  {row['put_oi']:,}")
        cw = f"${row['call_wall']:.0f}" if row['call_wall'] else "N/A"
        pw = f"${row['put_wall']:.0f}"  if row['put_wall']  else "N/A"
        mp = f"${row['max_pain']:.0f}"  if row['max_pain']  else "N/A"
        print(f"           Call Wall: {cw}   Put Wall: {pw}   Max Pain: {mp}")
        print(f"  GammaBias: {row['gamma_bias']:+.4f}")
        print(f"  Historical ({row['hist_samples']} samples): "
              f"1d win {row['hist_win1']}% avg {row['hist_avg1']:+.2f}% | "
              f"3d win {row['hist_win3']}% avg {row['hist_avg3']:+.2f}% | "
              f"5d win {row['hist_win5']}% avg {row['hist_avg5']:+.2f}%")
        print(f"  Scores: Oversold={row['oversold_score']} | Reversal={row['reversal_score']} "
              f"| Options={row['options_score']} | Historical={row['hist_score']}")
        print(f"  Timing: {row['timing']}")
        print(f"  Reason: {row['reason']}")


def export_csv(top10: list[dict], path: str) -> None:
    df = pd.DataFrame(top10)
    # Drop internal fields if any
    df = df.drop(columns=[c for c in df.columns if c.startswith("_")], errors="ignore")
    df.to_csv(path, index=False)
    print(f"\n[INFO] Results exported to: {os.path.abspath(path)}")


def print_summary_notes(top10: list[dict]) -> None:
    print("\n" + "=" * 100)
    print("  SCREENER METHODOLOGY NOTES")
    print("=" * 100)
    print("""
SIGNAL ACCURACY:
  EXACT:      RSI, StochRSI, Bollinger Bands, EMA/SMA, ATR, MACD, ROC, candle structure,
              volume metrics, historical win rates and average returns.
  ESTIMATED:  Gamma bias (proxy using OI × DTE weight × distance from spot).
              True gamma requires Black-Scholes Greeks not available from free data.
  APPROXIMATE: Put/call walls = highest OI strike above/below spot (not dollar-weighted).
               Max pain = standard calculation but limited to available option chain data.

MOST IMPORTANT SIGNALS FOR SHORT-TERM UPSIDE:
  1. Bullish reversal score (MACD cross, hammer candle, volume capitulation)
  2. Options score (low PCR, positive gamma bias, supportive put wall)
  3. Historical 3-day win rate and average return
  4. RSI + StochRSI depth (sets up the oversold base)

DATA LIMITATIONS:
  - Free-tier yfinance data; options chains may be incomplete.
  - Historical simulation uses RSI as oversold proxy only (simplified).
  - Gamma bias is approximated, not institutional-grade.
  - Intraday VWAP not included (requires minute-level data).
  - Results reflect close-of-prior-day data until next market close.
""")
    if top10:
        print(f"  TOP PICK: #{1} {top10[0]['ticker']} (Score: {top10[0]['composite_score']})")
        print(f"  Reason:   {top10[0]['reason']}")
        intraday = [r for r in top10 if "intraday" in r["timing"].lower() or "same" in r["timing"].lower()]
        multiday = [r for r in top10 if "multi" in r["timing"].lower()]
        if intraday:
            print(f"\n  BEST FOR SAME-DAY: {', '.join(r['ticker'] for r in intraday[:3])}")
        if multiday:
            print(f"  BEST FOR 1–5 DAYS: {', '.join(r['ticker'] for r in multiday[:3])}")

# ==============================================================================
#  MAIN
# ==============================================================================

def main():
    print("\n" + "=" * 60)
    print("  S&P 500 BULLISH SCREENER  ─  Starting...")
    print("=" * 60)

    # ── Step 1: Get universe ──────────────────────────────────────────────────
    tickers = get_sp500_tickers()

    # ── Step 2: Stage 1 broad scan ────────────────────────────────────────────
    print(f"\n[Stage 1] Scanning {len(tickers)} S&P 500 stocks...")
    stage1_results = stage1_scan(tickers)

    if not stage1_results:
        print("[ERROR] No candidates found. Try relaxing thresholds in CONFIG.")
        return

    top_n = stage1_results[:CONFIG["stage1_top_n"]]
    print(f"[Stage 1] {len(stage1_results)} candidates scored. "
          f"Carrying top {len(top_n)} into Stage 2.")

    # ── Step 3: Stage 2 deep review ───────────────────────────────────────────
    final_top10 = stage2_deep_review(top_n)

    # ── Step 4: Output ────────────────────────────────────────────────────────
    print_ranked_table(final_top10)
    print_detail_cards(final_top10)
    export_csv(final_top10, CONFIG["output_csv"])
    print_summary_notes(final_top10)


if __name__ == "__main__":
    main()