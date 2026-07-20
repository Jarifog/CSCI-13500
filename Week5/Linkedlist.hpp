#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <iostream>
#include <stdexcept>

// This is one Node in our linked list.
// It holds a value and a pointer to the next Node.
struct Node
{
    int value;
    Node* next;

    // Constructor: sets the value and makes next point to nothing (nullptr).
    Node(int passed_value) : value(passed_value), next(nullptr) {}
};

// Represents a linked list that keeps track of the first node and the number of nodes.

class LinkedList
{

    //function declarations for the linked list class. These functions allow for inserting nodes at the end or front of the list, checking for the existence of a value, removing nodes, printing values and addresses, getting values at specific positions, reversing the list, inserting nodes at specific positions, getting the size of the list, and merging two lists by intertwining their nodes.
public:
    // Default constructor. Starts with an empty list.
    LinkedList();

    // Destructor. Frees up all the memory we used.
    ~LinkedList();

    // Adds a value to the end of the list.
    void InsertNode(const int value);

    // Adds a value to the front of the list.
    void InsertNodeFront(const int value);

    // Checks if a value exists somewhere in the list.
    bool Contains(const int value) const;

    // Removes the node at a given position (1-based). Returns true if it worked.
    bool Remove(const int position);

    // Prints out all the values in the list, like: 10 -> 23 -> 4 -> nullptr
    void PrintValues() const;

    // Prints out the position and memory address of every node.
    void PrintAddresses() const;

    // Returns the value stored at a given position (1-based).
    // Throws std::out_of_range if the position doesn't exist.
    int GetValueAtPosition(const int position) const;

    // Reverses the list and hands ownership over to a brand new list.
    // The original list is left empty after this runs.
    LinkedList* ReverseList();

    // Inserts a value at a specific position (1-based).
    // Throws std::out_of_range if the position is invalid.
    void InsertNodeAt(const int value, const int position);

    // Returns how many nodes are in the list right now.
    int GetSize() const;

    // Makes a brand new list by alternating nodes from this list and another one.
    LinkedList* MergeIntertwine(const LinkedList& second_list) const;

private:
    int size_;
    Node* head_;
};

#endif  