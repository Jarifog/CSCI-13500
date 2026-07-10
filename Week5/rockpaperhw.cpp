#include <iostream>
#include <random>
#include <string>

void displayWelcomeMessage()
{
    std::cout << "Updated Rock paper scissors game v2" << std::endl;
    std::cout << "First to 2 wins." << std::endl;
    std::cout << "Enter either: Rock, Paper, or Scissor." << std::endl;
}

std::string getPlayerChoice()
{
    std::string player_move = "";

    std::cout << "Choose either Rock, Paper or Scissor: ";
    std::cin >> player_move;

    while (player_move != "Rock" && player_move != "Paper" && player_move != "Scissor")
    {
        std::cout << "Error: Please type Rock, Paper, or Scissor: ";
        std::cin >> player_move;
    }

    return player_move;
}

std::string getBotChoice()
{
    int bot_move = rand() % 3;

    if (bot_move == 0)
    {
        return "Rock";
    }
    else if (bot_move == 1)
    {
        return "Paper";
    }
    else
    {
        return "Scissor";
    }
}

bool playerWinsRound(std::string player_move, std::string bot_pick)
{
    if (player_move == "Rock" && bot_pick == "Scissor")
    {
        return true;
    }
    else if (player_move == "Paper" && bot_pick == "Rock")
    {
        return true;
    }
    else if (player_move == "Scissor" && bot_pick == "Paper")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void displayFinalResult(int player_score, int bot_score)
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
    std::string player_move = "";
    std::string bot_pick = "";

    displayWelcomeMessage();

  
    for (int rounds = 0; rounds < 3; rounds++)
    {
        
        if (player_score >= 2 || bot_score >= 2)
        {
            break;
        }

        std::cout << "\nRound " << rounds + 1 << std::endl;

        // ask for user input and validate it
        player_move = getPlayerChoice();

        // generate bot input
        bot_pick = getBotChoice();

        std::cout << "You chose: " << player_move << std::endl;
        std::cout << "Bot chose: " << bot_pick << std::endl;

        // figure out the score
        if (player_move == bot_pick)
        {
            std::cout << "Tie!" << std::endl;
        }
        else if (playerWinsRound(player_move, bot_pick))
        {
            std::cout << "Player wins this round!" << std::endl;
            player_score++;
        }
        else
        {
            std::cout << "Bot wins this round!" << std::endl;
            bot_score++;
        }
    }

    // display final results
    displayFinalResult(player_score, bot_score);

    return 0;
}