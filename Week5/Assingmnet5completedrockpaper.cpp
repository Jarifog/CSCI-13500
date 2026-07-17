#include <iostream>
#include <random>

void DisplayWelcome()
{
    std::cout << "Welcome to Jarif's Rock, Paper, Scissor!" << std::endl;
    std::cout << "Please enter Rock, Paper, or Scissor." << std::endl;
    std::cout << "Rock beats Scissor, Scissor beats Paper, and Paper beats Rock." << std::endl;
    std::cout << "First to reach 2 points wins the game." << std::endl;
    std::cout << std::endl;
}

std::string PlayerChoice()
{
    std::string player_move = "";

    std::cout << "Choose rock, paper or scissor: ";
    std::cin >> player_move;

    while (player_move != "Rock" && player_move != "Paper" &&
           player_move != "Scissor" && player_move != "rock" &&
           player_move != "paper" && player_move != "scissor")
    {
        std::cout << "Invalid input, please try again: ";
        std::cin >> player_move;
    }

    if (player_move == "rock")
    {
        player_move = "Rock";
    }
    else if (player_move == "paper")
    {
        player_move = "Paper";
    }
    else if (player_move == "scissor")
    {
        player_move = "Scissor";
    }

    return player_move;
}

std::string BotChoice()
{
    int bot_move = rand() % 3;
    std::string bot_pick = "";

    if (bot_move == 0)
    {
        bot_pick = "Rock";
    }
    else if (bot_move == 1)
    {
        bot_pick = "Paper";
    }
    else
    {
        bot_pick = "Scissor";
    }

    return bot_pick;
}

bool PlayRound(std::string player_move, std::string bot_pick,
               int& player_score, int& bot_score)
{
    if (player_move == bot_pick)
    {
        std::cout << "This round is a tie!" << std::endl;
        return true;
    }
    else if (player_move == "Scissor" && bot_pick == "Paper")
    {
        player_score++;
        std::cout << "Player wins this round!" << std::endl;
    }
    else if (player_move == "Paper" && bot_pick == "Rock")
    {
        player_score++;
        std::cout << "Player wins this round!" << std::endl;
    }
    else if (player_move == "Rock" && bot_pick == "Scissor")
    {
        player_score++;
        std::cout << "Player wins this round!" << std::endl;
    }
    else
    {
        bot_score++;
        std::cout << "Bot wins this round!" << std::endl;
    }

    return false;
}

void DisplayScore(int rounds_played, int player_score, int bot_score)
{
    std::cout << "Rounds played: " << rounds_played << std::endl;
    std::cout << "Player points: " << player_score << std::endl;
    std::cout << "Bot points: " << bot_score << std::endl;
}

void DisplayWinner(int player_score, int bot_score)
{
    if (player_score > bot_score)
    {
        std::cout << "Player wins!" << std::endl;
    }
    else if (bot_score > player_score)
    {
        std::cout << "Bot wins!" << std::endl;
    }
    else
    {
        std::cout << "Tie!" << std::endl;
    }
}

int main()
{
    int player_score = 0;
    int bot_score = 0;
    int rounds_played = 0;

    DisplayWelcome();

    for (int rounds = 0; rounds < 3; rounds++)
    {
        if (player_score >= 2 || bot_score >= 2)
        {
            break;
        }

        std::string player_move = PlayerChoice();
        std::string bot_pick = BotChoice();

        std::cout << "Bot chose: " << bot_pick << std::endl;
            //suggestion added by Ai. 
        bool tie = PlayRound(player_move, bot_pick,
                             player_score, bot_score);

        if (tie == true)
        {
            rounds--;
        }

        rounds_played++;

        DisplayScore(rounds_played, player_score, bot_score);
    }

    DisplayWinner(player_score, bot_score);

    return 0;
}