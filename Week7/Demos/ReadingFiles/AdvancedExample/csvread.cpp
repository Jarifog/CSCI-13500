#include <iostream>  
#include <fstream> 
#include <string> 
#include <sstream> 
#include <vector>
// a struct of 132 
// 128 for the string stuff 
// 4 for the int
struct Console{
    std::string name = "";
    std::string brand = "";
    int year = 0;
    int price = 0;
    std::string generation = "";
    std::string console_type = "";

    Console(){};

    Console(std::string input_name, std::string input_brand, int input_year, int input_price,
            std::string input_generation, std::string input_console_type) : name(input_brand),
            brand(input_brand), year(input_year), price(input_price), generation(input_generation),
            console_type(input_console_type){

            };

};

int main(){
    const std::string file_name = "modern_consoles_data.csv";
    std::ifstream actual_file;

    // older c++ version's file operations only take c type string, this would be used to convert the file name to the correct type
    // const char* second = file_name.c_str();

    actual_file.open(file_name);

    std::vector<Console> consoles{};

    std::string line = "";

    std::getline(actual_file, line); // take care of the  first line;
    
    std::string read_name = "";
    std::string read_brand = "";
    std::string read_year = "";
    std::string read_price = "";
    std::string read_generation = "";
    std::string read_console_type = "";

    
    while(getline(actual_file, line)){
        std::istringstream iss(line);
        getline(iss, read_name, ',');
        getline(iss, read_brand, ',');
        getline(iss, read_year, ',');
        getline(iss, read_price, ',');
        getline(iss, read_generation, ',');
        getline(iss, read_console_type, ',');

        // create object
        Console creation;
        creation.name = read_name; creation.brand = read_brand;
        creation.year = std::stoi(read_year);
        creation.price = std::stoi(read_price);
        creation.generation = read_generation;
        creation.console_type = read_console_type;

        consoles.push_back(creation);
    }

    // quick parse of the vector: print each object's data members, spaced out
    for(const Console& console : consoles){
        std::cout << "Name:        " << console.name << "\n";
        std::cout << "Brand:       " << console.brand << "\n";
        std::cout << "Year:        " << console.year << "\n";
        std::cout << "Price:       " << console.price << "\n";
        std::cout << "Generation:  " << console.generation << "\n";
        std::cout << "Type:        " << console.console_type << "\n";
        std::cout << "\n";
    }

    return 0;
}