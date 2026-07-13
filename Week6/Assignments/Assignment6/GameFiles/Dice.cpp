#include "Dice.h"
#include <cstdlib>
#include <ctime>


//used ai and was told to use srand time()
int RollDice() {
    static bool first = true;

    if (first) {
        srand(time(0));
        first = false;
    }

    return rand() % 6 + 1;
}