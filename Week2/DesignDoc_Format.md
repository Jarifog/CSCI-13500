# Program Design Document

## Program Name

(Name of the assignment)

## Purpose

Briefly explain what the program does and what problem it solves.

---

## Inputs

List all inputs the program will receive.

Example:

* Student name
* Homework score
* Quiz score
* Exam score

---

## Outputs

List what the program will display or produce.

Example:

* Student name
* Final grade
* Letter grade

---

## Variables

| Variable | Type   | Purpose                   |
| -------- | ------ | ------------------------- |
| score    | double | Stores test score         |
| average  | double | Stores calculated average |
| grade    | char   | Stores letter grade       |

---

## Key Design Choices

Explain any important decisions you made when designing the program.

Examples:

* Why did you use a loop instead of repeating code?
* Why did you choose a function for a task?
* Why did you use an array/vector instead of separate variables?
* Why did you use an if-else statement instead of a switch statement?

Example:
"I used a loop to process multiple scores because it reduces code duplication and makes the program easier to modify if the number of scores changes."

---

## Program Steps (Algorithm)

1. Get input from the user.
2. Validate the input if necessary.
3. Perform calculations.
4. Determine results.
5. Display output.

---

## Functions

### Function: calculateAverage()

Purpose: Calculates the average score.

### Function: determineGrade()

Purpose: Converts a numeric score into a letter grade.

---

## Sample Input/Output

Input:
Homework: 90
Quiz: 85
Exam: 95

Output:
Final Average: 90
Letter Grade: A

---

## Testing

### Test Case 1

Input: Normal values

Expected Result: Correct calculation

### Test Case 2

Input: Minimum values

Expected Result: Correct handling

### Test Case 3

Input: Maximum values

Expected Result: Correct handling
