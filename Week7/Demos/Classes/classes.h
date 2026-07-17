// Purely for declarations
#ifndef PLAYER_HEADER_
#define PLAYER_HEADER_

#include <iostream> 

class Player{ 
    private:
        
    std::string name_;
    std::string move_;
    int score_;

    public: 
    //functions 

    //constructor
    Player(std::string chosen_name = "John Player", int starting_score = 0);

    //functions to interact with move 
    std::string GetMove() const;
    void SetMove();

    //functions to interact with score
    int GetScore() const;
    void SetScore();

    //Get name
    std::string GetName() const;

    ~Player(); // without it, possible memory leak! 

    std::string +();

};

#endif 