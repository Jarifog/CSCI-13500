#include <iostream>
#include <random>


int main(){

    
    int player_score = 0;
    int bot_score = 0;
    std::string player_move = "";
    int bot_move = 0;
    std::string bot_pick = ""; 
    int rounds_played = 0;
    
      
    std::cout << "Welcome to Jarif's Rock, Paper, Scissor!" << std::endl;
    std::cout << "Please enter either Rock, Paper, or Scissor, any other input will be considered invalid." << std::endl;
    std::cout << "Rock beats Scissor, Scissor beats Paper, and Paper beats Rock." << std::endl;
    std::cout << "First to reach 2 points wins the game." << std::endl;
    std::cout << std::endl;


    
    for (int rounds = 0; rounds < 3; rounds++){

        
        if (player_score >= 2 || bot_score >= 2){
            break;
        }

       
        std::cout << "Choose rock, paper or scissor: ";
        std::cin >> player_move;


        if (player_move != "Rock" && player_move != "Paper" && player_move != "Scissor" && player_move != "rock" && player_move != "paper" && player_move != "scissor"){
            std::cout << "Invalid input, please try again." << std::endl;
            rounds--;
            continue;
        }
    
        if (player_move == "rock"){
            player_move = "Rock";
        }
        else if (player_move == "paper"){
            player_move = "Paper";
        }
        else if (player_move == "scissor"){
            player_move = "Scissor";
        }

        

        
        bot_move = rand() % 3;

        if (bot_move == 0){
            bot_pick = "Rock";
        }
        else if (bot_move == 1){
            bot_pick = "Paper";
        }
        else{
            bot_pick = "Scissor";
        }

        std::cout << "Bot chose: " << bot_pick << std::endl;


    
        if (player_move == bot_pick){
            std::cout << "This round is a tie!" << std::endl;
            rounds--; }

        else if (player_move == "Scissor" && bot_pick == "Paper"){
            player_score++;
            std::cout << "Player wins this round!" << std::endl;
}
        else if (player_move == "Paper" && bot_pick == "Rock"){
            player_score++;
            std::cout << "Player wins this round!" << std::endl;
}
        else if (player_move == "Rock" && bot_pick == "Scissor"){
            player_score++;
            std::cout << "Player wins this round!" << std::endl;
        }
        else{
            bot_score++;
            std::cout << "Bot wins this round!" << std::endl;
}




    rounds_played++;
    std::cout << "Rounds played: " << rounds_played << std::endl;
    std::cout << "Player points: " << player_score << std::endl;
    std::cout << "Bot points: " << bot_score << std::endl;

    



    }
    
    if (player_score > bot_score){
        std::cout << "Player wins!" << std::endl;
    }
    else if (bot_score > player_score){
        std::cout << "Bot wins!" << std::endl;
    }
    else{
        std::cout << "Tie!" << std::endl;
    }




}