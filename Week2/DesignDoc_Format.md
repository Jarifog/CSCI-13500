# Program Design Document

## Program Name

(Name of the assignment)

## Purpose

Briefly explain what the program does and what problem it solves.

Example:
"The program calculates a student's final grade based on homework, quizzes, and exam scores."

---

## Inputs

List all inputs the program will receive.

EXAMPLE:

* Student name
* Homework score
* Quiz score
* Exam score

---

## Outputs

List what the program will display or produce.

EXAMPLE:

* Student name
* Final grade
* Letter grade

---

## Variables

List important variables.

EXAMPLE:
| Variable | Type   | Purpose                   |
| -------- | ------ | ------------------------- |
| score    | double | Stores test score         |
| average  | double | Stores calculated average |
| grade    | char   | Stores letter grade       |

---

## Key Design Choices

Write any design choice that you made over all possible choices and why. 

## Program Steps (Algorithm)

1. Get input from the user.
2. Validate the input if necessary.
3. Perform calculations.
4. Determine results.
5. Display output.

---

## Functions (if required)

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

Test Case 1:

* Input: Normal values
* Expected Result: Correct calculation

Test Case 2:

* Input: Minimum values
* Expected Result: Correct handling

Test Case 3:

* Input: Maximum values
* Expected Result: Correct handling
