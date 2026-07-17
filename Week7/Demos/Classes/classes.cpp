// Purely Implementation
#include "classes.h"


    Player::Player(std::string chosen_name, int starting_score){
        name_ = chosen_name;
        score_ = starting_score;
    }

    //functions to interact with move 
    std::string Player::GetMove() const{
        return move_;
    }
    void Player::SetMove(){}

    //functions to interact with score
    int Player::GetScore() const{
        return score_;
    }
    void Player::SetScore(){}

    //Get name
    std::string Player::GetName() const{
        return name_;
    }

    Player::~Player(){}

