# Refactor Rock Paper Scissor 

Did you notice how big your program has gotten?

When we first started writing programs, putting everything inside ```main()``` wasn't a big deal. But now your Rock, Paper, Scissors game has grown quite a bit! Imagine how difficult it would be to find a bug or add a new feature if every line of code lived in one giant function.

Programmers solve this problem by breaking large programs into smaller, reusable functions. Each function has one job, making the program easier to read, test, and maintain.

Your mission is to refactor your existing Rock, Paper, Scissors game by moving pieces of your code into well-designed functions.

## Your Task

Starting with the program you wrote for the assignment 2.5, reorganize your code so that ```main()``` acts as the "manager" of your program. Instead of doing all the work itself, it should call functions to complete each part of the game.

**At a minimum, create functions for:**

- Displaying the welcome message and instructions.
- Getting and validating the player's choice.
- Generating the computer's random choice.
- Keep current score of the player and computer, and output a message if one of them wins
- Displaying the results.
- Any additional features you added in assignment 2.5 and can turn into a function

Feel free to create additional functions if they make your program cleaner!

## Requirements
- Your program must still work exactly as it did before.
- Use meaningful function names.
- Each function should perform one specific task.
- Use parameters and return values whenever they make sense.
- Keep your code properly formatted and commented.
- ```main()``` should be much shorter than it was before and should mainly consist of function calls.
- Use Google Style Guides for C++ Functions