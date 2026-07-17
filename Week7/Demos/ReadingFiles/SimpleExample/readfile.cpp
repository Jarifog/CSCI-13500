#include <iostream>
#include <fstream>
#include <string>

int main(){

    // Open the file 
    std::ifstream FileReaderObject("CatStory.txt");

    // Check if it actually opened 
    if (!FileReaderObject.is_open()){
        std::cout << "File not found!" << std::endl;
        return 0;
    }

    std::string the_line = {};
    // Read the file line by line 
    while(std::getline(FileReaderObject, the_line)){

        std::cout << the_line << std::endl;

    }

    // Close the file 
    FileReaderObject.close();

}