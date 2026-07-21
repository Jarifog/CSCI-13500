#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string input_file_name;
    std::string search_word;
    std::string replacement_word;
    std::string word;

    int replacement_count = 0;


    std::cout << "Enterinput file name: ";
    std::cin >> input_file_name;

    std::cout << "Enter the word you are searching for: ";
    std::cin >> search_word;

    std::cout << "Enter the replacement word: ";
    std::cin >> replacement_word;

    
    std::ifstream input_file(input_file_name);

    
    if (!input_file.is_open())
    {
        std::cout << "Error: Could not open the input file." << std::endl;



        return 1;
    }


    std::cout << "Warning: This program splits words by spaces only, so words separated by commas (like in a CSV) may not be matched correctly." << std::endl;

    std::ofstream output_file("output.txt");


    while (input_file >> word)
    {
    
        if (word == search_word)
        {
            word = replacement_word;
            replacement_count++;
        }

    
        output_file << word << " ";
    }

    
    input_file.close();
    output_file.close();

    
    std::cout << "The word \"" << search_word << "\" was found "  << replacement_count << " times." << std::endl;

    std::cout << "The modified text has been saved to output.txt."  << std::endl;

    return 0;
}