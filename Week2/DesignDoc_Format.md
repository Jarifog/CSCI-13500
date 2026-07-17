# Program Design Document

## Program Name

Assingmnet 2 Rock paper scissors 

## Purpose

Briefly explain what the program does and what problem it solves.

Updates the Rock paper scissor code, adding input valiadtion for wrong inputs, better ui and extensive game tracking. 

---

## Inputs

List all inputs the program will receive.

Example:

* Player_move: Rock, paper or scissors or technically invalid input. 
---

## Outputs

List what the program will display or produce.

*welcome message.
*Instructions explaining how the game works.
*An error message for invalid input.
*The bot’s choice.
*Whether the player, bot, or neither side won the round.
*The total number of rounds played.
*The player’s current points.
*The bot’s current points.
*The final winner of the game.

---

## Variables

| Variable       | Type                              
                                Purpose
| -------------- | ----------- |-------------------------------------------- |
| player_score   | int         | Stores the player’s current number of points |
| bot_score      | int         | Stores the bot’s current number of points    |
| player_move    | std::string | Stores the player’s selected move            |
| bot_move       | int         | Stores the random number for the bot’s move  |
| bot_pick       | std::string | Stores the bot’s selected move               |
| rounds_played  | int         | Stores the total number of rounds played     |
| rounds         | int         | Controls and tracks the game loop            |

---

## Key Design Choices

Explain any important decisions you made when designing the program.

Examples:

* Why did you use a loop instead of repeating code?
I used a for loop to keep the game going until the 3 rounds were completed. I also used a check for an early win 2-0
* Why did you choose a function for a task?
I used Main()
* Why did you use an if-else statement instead of a switch statement?

I used else if and if as it was easier to code the possible combinations of rock paper scissors results. 

I added input validation so the program only accepts Rock, Paper, or Scissor. Invalid input does not count as a round, and the player is asked to try again.

I allowed for both lowercase and capitalized inputs to make the game easier to use. Lowercase inputs are converted into capitalized versions before the winner is determined.

I used a random number between 0 and 2 to choose the bot’s move. Each number represents Rock, Paper, or Scissor.

Tied rounds do not count as one of the three deciding rounds because neither side earns a point. However, tied rounds are still included in the rounds_played counter because the round was completed.

I added the rounds-played counter and point tracker so the player can clearly follow the progress of the game.


---

## Program Steps (Algorithm)
1. Display the welcome message and game instructions.
1. Get input from the user either rock paper or scrioosrs
2. Validate the input if necessary.
4.Concert lowercase input to captailzized. 
5. generate random number from 0-2 each number value representing rock paper or scissors. 
6. Bot does either rock paper scissors. 

3. Perform calculations.
4. Determine results for who won or tie. 
6. add one point to winner 
7.add to rounds played
8. continue until a win occurs of the two rounds. 
5. Display output.

---

## Functions

### Function: Main()

Purpose: handeles the entire rock paper scissor game. 

## Sample Input/Output
Welcome to Jarif's Rock, Paper, Scissor!
Please enter either Rock, Paper, or Scissor, any other input will be considered invalid.
Rock beats Scissor, Scissor beats Paper, and Paper beats Rock.
First to reach 2 points wins the game.

Choose rock, paper or scissor: rock
Bot chose: Paper
Bot wins this round!
Rounds played: 1
Player points: 0
Bot points: 1
---

## Testing

### Test Case 1

Input: lower case rock 

Expected Result: converts to Rock



Choose rock, paper or scissor: rock
Bot chose: Paper
Bot wins this round!
Rounds played: 1
Player points: 0
Bot points: 1