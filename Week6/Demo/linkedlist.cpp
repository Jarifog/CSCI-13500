#include <iostream>


struct Node{

    std::string name = {};
    Node* next_nodes_address = nullptr;

    //constructor: tells the computer how to build your custom data type
    Node(std::string user_data){
        //setting its own "name" variable to the user_data
        //'this' is how an object refers to itself
        this -> name = user_data;
    }
};

int main(){

    Node head("start");
    Node* current_node = &head; 
    std::string user_input = {};

    while (std::cin >> user_input){
        if (user_input == "q"){
            break;
        }

        current_node -> next_nodes_address = new Node(user_input);
        current_node = current_node -> next_nodes_address;
    }

    current_node = &head; 
    while (current_node){
        std::cout << current_node->name << " -> ";
        
        
        Node* next_node = current_node->next_nodes_address;
        delete current_node;
        current_node = nullptr;    // Prevent dangling pointers
        current_node = next_node;
    }

}

