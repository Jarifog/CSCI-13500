#include "classes.h"
#include <iostream>
#include <string>
#include <cmath>


enum Moves{
    ROCK = 1, // 0
    PAPER = 232, // 1
    SCISSOR = 21  // 2
};

int main(){
    
    Player BotPlayer("Bot");
    Player HumanPlayer;
    Player* ptr = BotPlayer;

    int move = PAPER;

    // std::cout << HumanPlayer.GetName() << std::endl;
    // std::cout << BotPlayer.GetName() << std::endl;
    std::cout << PAPER << std::endl;

    delete BotPlayer
    ptr = nullptr;

    

    return 0;
}