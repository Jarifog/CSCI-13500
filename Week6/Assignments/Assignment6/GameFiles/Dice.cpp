#include "Dice.h"
#include <cstdlib>
#include <ctime>

int RollDice() {
    static bool first = true;

    if (first) {
        srand(time(0));
        first = false;
    }

    return rand() % 6 + 1;
}