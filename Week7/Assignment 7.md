# Assignment: Word Search and Replace Using File I/O


Write a C++ program that searches for a word in a text file, counts how many times it appears, and creates a new file where every occurrence of that word is replaced with another word chosen by the user.


## Assignment Description

Your program should prompt the user for:

1. The input file name.
2. The word to search for.
3. The replacement word.

The program will:

1. Open the input file.
2. Read the file one word at a time.
3. Count how many times the search word appears.
4. Replace every occurrence of the search word with the replacement word.
5. Write the modified text to a new file named `output.txt`.
6. Display the total number of replacements made.


## Example Input File (`story.txt`)

```text
The cat chased the mouse.
The dog watched the cat.
The cat was happy.
```

## Example Program Run

```text
Enter the input file name: story.txt
Enter the word to search for: cat
Enter the replacement word: tiger
```

### Example Output

```text
The word "cat" was found 3 times.
The modified text has been saved to output.txt.
```


### Contents of `output.txt`

```text
The tiger chased the mouse.
The dog watched the tiger.
The tiger was happy.
```

## Program Requirements

Your program must:

- Use `ifstream` to open the input file.
- Use `ofstream` to create `output.txt`.
- Display an error message if the input file cannot be opened.
- Read the input file one word at a time.
- Compare each word to the search word.
- Replace matching words with the replacement word.
- Keep a count of the number of replacements made.
- Write all words (modified or unchanged) to the output file.
- Close both files before the program ends.


## Notes

- You may assume words are separated by spaces.
- You do **not** need to ignore punctuation or letter case for this assignment. For example, `cat` and `cat.` are considered different words.
- Preserve the order of the words when writing the new file.


## Bonus Challenges (Optional)

Choose one or more of the following enhancements:

1. Make the search **case-insensitive**.
2. Replace words even when followed by punctuation (e.g., `cat,`, `cat.`, `cat!`).
3. Allow the user to specify the output file name.
4. Display the total number of words processed.
5. Display the percentage of words that were replaced.


## Constraints

**Do not use**:

- `vector`
- `map`
- Regular expressions
- Advanced string-processing libraries
- Third-party libraries