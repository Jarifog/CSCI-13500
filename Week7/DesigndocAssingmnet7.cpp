# Program Design Document

## Program Name

Assignment 7 Word Search and Replace Using File I/O

## Purpose

Briefly explain what the program does and what problem it solves.

The program opens a text file which searches for a word chosen by the user, and replaces every matching word with another word known as the replacement word, It counts/ creates a counter on how many replacements were made and saves the changed text into a new file named output.txt.

---

## Inputs

List all inputs the program will receive.

Example:

- input_file_name: The name of the text file the user wants to open.
- search_word: The word the user wants to find.
- replacement_word: The word that will replace the search word.

---

## Outputs

List what the program will display or produce.

- Message asking for the user input file name.
- Message asking for the word to search for.
- Message asking for the replacement word.
- An error message if the input file cannot be opened.
- The total number of times the search word was found.
- A message saying the modified text was saved to output.txt.
- A new file named output.txt containing the changed text.

---

## Variables

| Variable | Type | Purpose |
|---|---|---|
| input_file_name | std::string | Stores the name of the input file entered by the user |
| search_word | std::string | Stores the word the user wants to find |
| replacement_word | std::string | Stores the word that will replace the search word |
| word | std::string | Stores each word being read from the input file |
| replacement_count | int | Stores the total number of replacements made |
| input_file | std::ifstream | Opens and reads the input text file |
| output_file | std::ofstream | Creates and writes to output.txt |

---

## Key Design Choices

Explain any important decisions you made when designing the program.

### Why did you use a loop instead of repeating code?

I used a while loop because the program does not know how many words are inside the file. The loop continues reading words until there are no more words left.

### Why did you choose a function for a task?

I used Main() to handle the entire program because the assignment was simple and did not require separate functions.

### Why did you use an if statement?

I used an if statement to compare each word from the file to the search word. If both words match, the program replaces the word and adds one to replacement_count.

I used std::ifstream to open and read the input file.

I used std::ofstream to create output.txt and write the modified words into it.

I used is_open() to check if the input file opened correctly. If the file does not open, the program displays an error message.

I read the file one word at a time because that was required by the assignment.

The program is also case-sensitive and punctuation sensitive, so cat and Cat are considered different words, as well as cat and cat. are considered different words.

---

## Program Steps (Algorithm)

1. Create variables for the input file name, search word, replacement word, current word, and replacement count.
2. Set replacement_count equal to 0.
3. Ask the user to enter the input file name.
4. Ask the user to enter the word they are searching for.
5. Ask the user to enter the replacement word.
6. Open the input file using std::ifstream.
7. Check if the input file opened successfully.
8. If the file did not open, display an error message and end the program.
9. Create output.txt using std::ofstream.
10. Read the input file one word at a time.
11. Compare the current word to the search word.
12. If the words match, replace the current word with the replacement word.
13. Add one to replacement_count.
14. Write the current word to output.txt.
15. Continue until there are no more words in the input file.
16. Close the input file.
17. Close the output file.
18. Display the number of replacements made.
19. Display that the modified text was saved to output.txt.

---

## Functions

### Function: Main()

Purpose: Handles the entire word search and replace program.

---

## Sample Input/Output

Enter input file name: story.txt  
Enter the word you are searching for: cat  
Enter the replacement word: tiger  
Warning: This program splits words by spaces only, so words separated by commas (like in a CSV) may not be matched correctly.  
The word "cat" was found 3 times.  
The modified text has been saved to output.txt.

Contents of output.txt:

The tiger chased the mouse. The dog watched the tiger. The tiger was happy.

---

## Testing

### Test Case 1 Example

Example Input file contents:

The cat chased the mouse.  
The dog watched the cat.  
The cat was happy.

Input:

input_file_name: story.txt  
search_word: cat  
replacement_word: tiger

Expected Result:

The program replaces all three uses of cat with tiger.

The program displays:

Warning: This program splits words by spaces only, so words separated by commas (like in a CSV) may not be matched correctly.  
The word "cat" was found 3 times.  
The modified text has been saved to output.txt.

output.txt contains:

The tiger chased the mouse. The dog watched the tiger. The tiger was happy.