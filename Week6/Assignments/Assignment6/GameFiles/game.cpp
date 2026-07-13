// This is the game loop. Your job is to implement the functions/methods
// it calls: RollDice() in Dice.cpp, and the Snake methods (functions) in Snake.cpp.
 
#include <iostream>
#include "Dice.h"
#include "Snake.h"
 
const int MAX_ROUNDS = 20;
 
int main() {
    std::cout << "=== KILL THE SNAKE ===\n\n";
 
    Snake mySnake;
    std::cout << "The snake awakens...\n";
    mySnake.PrintSnake();
    std::cout << "\n";
 
    int round = 1;
    bool snake_is_dead = false;
 
    while (round <= MAX_ROUNDS) {
        std::cout << "--- Round " << round << " ---\n";
 
        int roll = RollDice();
        std::cout << "You rolled a " << roll << "!\n";
 
        int killedCount = mySnake.Kill(roll);
        std::cout << "You killed " << killedCount << " segment(s).\n";
        mySnake.PrintSnake();
 
        if (mySnake.GetLength() == 0) {
            snake_is_dead = true;
            break;
        }
 
        if (round % 2 == 0) {
            int regenRoll = RollDice();
            mySnake.Regenerate(regenRoll);
            std::cout << "The snake regenerates " << regenRoll
                      << " segment(s)!\n";
            mySnake.PrintSnake();
        }
 
        std::cout << "\n";
        round++;
    }
 
    std::cout << "\n=== GAME OVER ===\n";
    if (snake_is_dead) {
        std::cout << "You killed the snake in " << round << " round(s)! You win!\n";
    } else {
        std::cout << "The snake survived " << MAX_ROUNDS
                  << " rounds. It wins this time.\n";
    }
 
    return 0;
}
 
