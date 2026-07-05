#include <iostream>


int main(){

    int age = 20;

    if (age >= 21){
        std::cout << "You are legally able to drink.";
    }

    else{
        std::cout << "You are a minor!";
    }

    /******************/

    (age >= 21) ? std::cout << "You are legally able to drink." : std::cout << "You are a minor!";
}





