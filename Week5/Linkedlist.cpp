#include "linkedlist.hpp"

// Constructor: creates an empty linked list using nullptr for the head and 0 for the size as there is no first node declared yet. 
LinkedList::LinkedList()
{
    
    head_ = nullptr;

    
    size_ = 0;
}

// Creates a new node and inserts it at the end of the linked list. A new node is created via Node* newNode = new Node(value) if head_ is nullptr that means the list is empty so head_ is dupated to point to a new node using head_= current -> inside the loop, until it traverses to the last node in which the last node is connected to the new node using cureent->next= newNode which is the new node created. Then size_ is increased because one node was added.
void LinkedList::InsertNode(int value)
{
     // this creates a new node with the given value and sets its next pointer to nullptr. to allow for the new node to be added to the end of the list.
    Node* newNode = new Node(value);

    // Check whether the list is currently empty. if list is empty, the new node becomes the first node in the list. if the list is not empty, we traverse the list to find the last node and connect it to the new node. which i used ai to figure out. 
    if (head_ == nullptr)
    {
        // The new node becomes the first node in the list.
        head_ = newNode;
    }
    else
    {
        // Start at the first node then use a while loop to traverse the list until we reach the last node. then we connect the last node to the new node. 
        Node* current = head_;

        // Move through the list until current reaches the final node.
        while (current->next != nullptr)
        {
            // Move current to the next node.
            current = current->next;
        }

        // Connect the final node to the new node.
        current->next = newNode;
    }

    // Increases the number of nodes in the list.
    size_++;
}

// Creates a new node and inserts it at the beginning of the list. The new node is first made to point to the current first node, or old head, using newNode->next = head_. Then head_ is updated to point to the new node using head_ = newNode, making it the new first node in the list. Then using size_ is increased because one node was added.

void LinkedList::InsertNodeFront(int value)
{
    //allows the new node to be added to the front of the list.
    Node* newNode = new Node(value);

    newNode->next = head_;

    
    head_ = newNode;

    size_++;
}

// Searches the list for a given value. if the value is found it returns true, if not it returns false. via a while loop that traverses the list and checks each node's value. We also use const to indicate that this function does not modify the linked list as suggested by ai. 
bool LinkedList::Contains(int value) const
{
    
    Node* current = head_;

    // while loop continues if there are still nodes to check.
    while (current != nullptr)
    {
    
        if (current->value == value)
        {
    
            return true;
        }

    
        current = current->next;
    }

     
    return false;
}

//// Removes a node from a given 1-based position. It first checks if the position is valid. If position is 1, head_ moves to the second node and the old head is deleted. If it is not then,  current moves to the node before the one being removed, skips over it using current->next = temp->next, and then deletes it. Size_ is decreased.
bool LinkedList::Remove(int position)
{
    
    if (position < 1 || position > size_)
    {
        return false;
    }

    // Handle removing the first node separately.
    if (position == 1)
    {
        // Temporarily store the address of the first node.
        Node* temp = head_;

        // Move head_ to the second node.
        head_ = head_->next;

        // Free the memory used by the old first node.
        delete temp;

        
        size_--;

        
        return true;
    }

    // Start at the first node.
    Node* current = head_;

    // Move current to the node directly before the node being removed.
    for (int i = 1; i < position - 1; i++)
    {
        current = current->next;
    }

    // Store the node that needs to be removed.
    Node* temp = current->next;

    // Make current skip over temp and point to the following node.
    current->next = temp->next;

    // Free the memory used by the removed node.
    delete temp;

   
    size_--;

    // The node was successfully removed.
    return true;
}

// Prints all values in the linked list. Slight use of Ai.  We use a while loop as we do not have an exact amount of values to print, so we continue until we reach the end of the list.
void LinkedList::PrintValues() const
{
    Node* current = head_;

    while (current != nullptr)
    {
        std::cout << current->value;

        if (current->next != nullptr)
        {
            std::cout << " -> ";
        }

        current = current->next;
    }
// we end in nullptr to indicate the end of the list. 
    std::cout << " -> nullptr" << std::endl;
}

// Prints the position and memory address of every node.
void LinkedList::PrintAddresses() const
{
    
    Node* current = head_;

    // Positions begin at 1.
    int pos = 1;

    // Continue until the end of the list is reached.
    while (current != nullptr)
    {
        
        std::cout << pos << " " << current << std::endl;

        // Move to the next node.
        current = current->next;

        // Increase the displayed position.
        pos++;
    }
}

// Returns the value stored at a given 1-based position.
int LinkedList::GetValueAtPosition(int position) const
{
    //gives invalid position when out of range
    if (position < 1 || position > size_)
    {
        throw std::out_of_range("Invalid position");
    }

    // Start at the first node.
    Node* current = head_;

    // Move current until it reaches the needed position. 
    for (int i = 1; i < position; i++)
    {
        current = current->next;
    }

    
    return current->value;
}

// Creates a new node and inserts it at a chosen 1-based position. First, the position is checked to make sure it is between 1 and size_ + 1. We allow size_ + 1 because this lets the new node be inserted after the current last node. If position is 1, the new node is made to point to the current head using newNode->next = head_. Then head_ is updated using head_ = newNode, making the new node the first node. If the position is greater than 1, current starts at head_ and moves to the node directly before the insertion position. The new node is first connected to the node after current using newNode->next = current->next. Then current is connected to the new node using current->next = newNode. This keeps the rest of the list connected. Then size_ is increased because one node was added.
void LinkedList::InsertNodeAt(int value, int position)
{

    if (position < 1 || position > size_ + 1)
    {
        throw std::out_of_range("Invalid position");
    }

  
    Node* newNode = new Node(value);

   
    if (position == 1)
    {
        // Make the new node point to the current first node.
        newNode->next = head_;

        // Make the new node the first node.
        head_ = newNode;

        // Increase the number of nodes.
        size_++;

        return;
    }

    // Start at the first node.
    Node* current = head_;

    // Move current to the node directly before the insert position. 
    for (int i = 1; i < position - 1; i++)
    {
        current = current->next;
    }

    // Make the new node point to the node currently after current.
    newNode->next = current->next;

    // Make current point to the new node.
    current->next = newNode;

    // Increase the number of nodes in the list.
    size_++;
}

int LinkedList::GetSize() const
{
    return size_;
}




LinkedList* LinkedList::ReverseList()
{
   //create empty list
    LinkedList* newList = new LinkedList();

    
    Node* prev = nullptr;

   
    Node* current = head_;

    // Temporarily stores the next node before changing a pointer. (saves the next node.)
    Node* temp = nullptr;

   //** heavily used Ai in this section, apparntly this is a three-pointer reversal pattern, noramlly when changing ->next it would make you lose acess to the rest of the list which is why we use temp here which saves the next node first.  */
    while (current != nullptr)
    {
        // Save the next node before changing current->next.
        temp = current->next;

        // Reverse current's pointer so it points backward. (reverses the arrow)
        current->next = prev;

        // Move prev forward to the current node.
        prev = current;

        // Move current forward to the saved next node.
        current = temp;
    }

   
// Reverses the list using prev, current, and temp. Temp saves the next node using temp = current->next before current->next is changed, then current points backward using current->next = prev, prev moves to current, and current moves to the saved node in temp. After all nodes are reversed, newList->head_ is set to prev and its size is copied, while the original head_ is set to nullptr and size_ is set to 0 because newList now owns the reversed nodes.


    newList->head_ = prev;

   
    newList->size_ = size_;

    
    head_ = nullptr;

    
    size_ = 0;

    
    return newList;
}
//heavily used ai for this section and commentation. 
// Creates a new linked list by alternating values from the current list and second_list. First, a new empty list is created using LinkedList* newList = new LinkedList(). The first pointer starts at head_, and the second pointer starts at second_list.head_. While first is not nullptr, the value from the first list is copied into newList using newList->InsertNode(first->value), and first moves to its next node. If second is not nullptr, its value is also copied into newList using newList->InsertNode(second->value), and second moves to its next node. This creates the alternating order. If the second list is longer, the second while loop copies all remaining values from the second list into newList. Then the new intertwined list is returned.
LinkedList* LinkedList::MergeIntertwine(
    const LinkedList& second_list) const
{
    // Dynamically create an empty list for the combined values.
    LinkedList* newList = new LinkedList();

    // Start at the first node of the current list.
    Node* first = head_;

    // Start at the first node of the second list.
    Node* second = second_list.head_;

    // Continue while the first list still has nodes.
    while (first != nullptr)
    {
        // Copy the current value from the first list into the new list.
        newList->InsertNode(first->value);

        // Move to the next node in the first list.
        first = first->next;

        // Check whether the second list still has a node available.
        if (second != nullptr)
        {
            // Copy the current value from the second list.
            newList->InsertNode(second->value);

            // Move to the next node in the second list.
            second = second->next;
        }
    }

   //heavily used ai**  using the while loop to copy any left over nodes from the second list into the new list. then using insertnode to copy the value into the new list and then moving to the next node in the second list.
    while (second != nullptr)
    {
       //Copies remaining values from the second list into the new list. 
        newList->InsertNode(second->value);

        // Move to the next remaining node.
        second = second->next;
    }

    // Return the newly created intertwined list.
    return newList;
}

// Destructor: deletes all the dynamic memory which are nodes used by the linked list.
LinkedList::~LinkedList()
{
    Node* current = head_;

    while (current != nullptr)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    head_ = nullptr;
    size_ = 0;
}