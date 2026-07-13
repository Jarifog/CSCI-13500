#pragma once
#include "Node.h"

class Snake {
public:
    Snake();                    // To build a snake with a starting number of segments
    ~Snake();                   // Prevent memory leaks. deallocate the space

    // Kills up to `count` segments from the FRONT of the snake.
    // If the snake has fewer than `count` segments left, kill all of them
    // and stop (do not go out of bounds / do not crash).
    // Returns the number of segments ACTUALLY killed.
    int Kill(int count);

    // Adds `count` new body parts (nodes) to the BACK (tail) of the snake.
    void Regenerate(int count);

    // Prints the snake's segments from head to tail, e.g.:
    // Snake: [12] -> [13] -> [14] -> [15]
    // Must not modify the snake in any way.
    void PrintSnake() const;

    int GetLength() const;


private:
    Node* head_;
    Node* tail_;   // think about why keeping a tail pointer is useful here
    int length_;
    int id_;      // used to give each new node a unique, increasing id

    static const int STARTING_LENGTH = 10;
};