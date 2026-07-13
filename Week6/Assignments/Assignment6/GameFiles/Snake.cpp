#include "Snake.h"
#include <iostream>

// TODO: Constructor
// - Build a snake with STARTING_LENGTH segments using `new`.
// - head should point to segment id 0 (or 1, your choice - just be consistent),
//   tail should point to the last segment created.
// - Set length and nextId appropriately.
Snake::Snake() {
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
    id_ = 0;

    for (int i = 0; i < STARTING_LENGTH; i++) {
        Node* newNode = new Node;
        newNode->body_part_ = id_;
        id_++;
        newNode->next_ = nullptr;

        if (head_ == nullptr) {
            head_ = newNode;
            tail_ = newNode;
        } else {
            tail_->next_ = newNode;
            tail_ = newNode;
        }

        length_++;
    }
}




// TODO: Destructor
// - Walk the list and delete every remaining node.
// - If you don't do this, running under valgrind/ASan will report a leak.
Snake::~Snake() {
    Node* current = head_;

    while (current != nullptr) {
        Node* nextNode = current->next_;
        delete current;
        current = nextNode;
    }
}

// TODO: kill()
// - Remove up to `count` nodes from the FRONT of the list, deleting each one.
// - Handle the edge case where the snake has fewer than `count` nodes left:
//   kill all remaining nodes and stop. Do not crash.
// - Update `length` (and `tail`/`head` if the snake becomes empty!).
// - Return the number of segments ACTUALLY killed.
int Snake::Kill(int count) {

    int killed_nodes = 0;

    while (head_ != nullptr && killed_nodes < count) {

        Node* temp = head_;

        head_ = head_->next_;

        delete temp;

        killed_nodes++;
        length_--;
    }

    if (head_ == nullptr) {
        tail_ = nullptr;
    }

    return killed_nodes;
}

// TODO: regenerate()
// - Append `count` new nodes to the BACK of the list using `new`.
// - Use `nextId` to assign each new node a unique, increasing id, and
//   increment `nextId` each time.
// - Update `tail` (and `head` if the snake was empty!) and `length`.
void Snake::Regenerate(int count) {

    for (int i = 0; i < count; i++) {

        Node* newNode = new Node;

        newNode->body_part_ = id_;
        id_++;

        newNode->next_ = nullptr;

        if (head_ == nullptr) {

            head_ = newNode;
            tail_ = newNode;
        }
        else {

            tail_->next_ = newNode;
            tail_ = newNode;
        }

        length_++;
    }
}

// TODO: print()
// - Walk the list from head to tail and print in the format:
//   Snake: [12] -> [13] -> [14] -> [15]
// - If the snake is empty, print something sensible like "Snake: (dead)".
// - This function must not modify the snake - use a `const Node*` to walk it.
void Snake::PrintSnake() const {

    if (head_ == nullptr) {
        std::cout << "Snake: (dead)\n";
        return;
    }

    std::cout << "Snake: ";

    const Node* current = head_;

    while (current != nullptr) {

        std::cout << "[" << current->body_part_ << "]";

        if (current->next_ != nullptr) {
            std::cout << " -> ";
        }

        current = current->next_;
    } //TODO

    std::cout << std::endl;
}

int Snake::GetLength() const {
    // TODO
    return length_;
}
