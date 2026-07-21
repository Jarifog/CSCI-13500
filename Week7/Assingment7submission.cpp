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

    // Ask the user for the file and words
    std::cout << "Enter the input file name: ";
    std::cin >> input_file_name;

    std::cout << "Enter the word to search for: ";
    std::cin >> search_word;

    std::cout << "Enter the replacement word: ";
    std::cin >> replacement_word;

    // Open the input file
    std::ifstream input_file(input_file_name);

    // Check if the input file opened
    if (!input_file.is_open())
    {
        std::cout << "Error: Could not open the input file."
                  << std::endl;

        return 1;
    }

    // Create the output file
    std::ofstream output_file("output.txt");

    // Read the input file one word at a time
    while (input_file >> word)
    {
        // Check if the current word matches
        if (word == search_word)
        {
            word = replacement_word;
            replacement_count++;
        }

        // Write the word to output.txt
        output_file << word << " ";
    }

    // Close both files
    input_file.close();
    output_file.close();

    // Display the results
    std::cout << "The word \"" << search_word << "\" was found "
              << replacement_count << " times." << std::endl;

    std::cout << "The modified text has been saved to output.txt."
              << std::endl;

    return 0;
}