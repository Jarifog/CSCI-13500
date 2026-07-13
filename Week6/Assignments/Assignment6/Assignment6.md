# Kill the Snake THE GAME

## Overview

Your manager at Rockstar Games wants you to develop a new AAA game called 'Kill the Snake THE GAME'.

The snake is a represented as a **singly linked list**. Each node is one segment of its body.
Every round you roll a die and kill that many snake parts from the front of the
snake. Every 2 rounds, the snake fights back and regenerates a random number
of segments. Kill it before it kills your round counter.

The senior engineer has already written the game loop for the team. You are **not** writing the game loop — that's done for you in `game.cpp`.
Your job is to implement the functions and class methods the game needs. This means
you need to read `game.cpp` carefully before writing anything, so you
understand exactly what each function is expected to do (its parameters, its
return value, and any side effects).

## Files

You are given:

- `game.cpp` — the game loop. **Do not modify this file. Unless you want to add more features to the game!**
- `Dice.h` — declaration of `RollDice()`.
- `Node.h` — the `Node` struct, already complete.
- `Snake.h` — the `Snake` class declaration, already complete. You implement its methods.

You will create/complete:

- `Dice.cpp`
- `Snake.cpp`

All files must compile together with **separate compilation**
Each `.cpp`file compiles into its own object file, and they get linked together.

**NOTE**: We will write the constructor and desctructor in class together on July 6th!

## Compiling

```
g++ -std=c++17 -Wall -c Dice.cpp -o Dice.o
g++ -std=c++17 -Wall -c Snake.cpp -o Snake.o
g++ -std=c++17 -Wall -c main.cpp -o main.o
g++ Dice.o Snake.o main.o -o game
```

