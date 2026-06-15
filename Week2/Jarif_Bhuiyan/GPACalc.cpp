#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

int main() {

    // Total Points (Credits multiplied by Grade Points ex: 3 credits multiplied by A (4 points) is 12. )
    double tp = 0.0;
    //total credits. 
    double tc = 0.0;
    //number of classes taken (starts at 0 increases by 1 for each class entered)
    int classesTaken = 0;
    //credit value from greater than 0 but less than 10. 
    double credits;
    // Letter grade (A, A-, B+, B, B-, C+, C, D, F, WU, FIN, FAB)
    std::string grade;
    // Number value of the letter grade. Example: A = 4.0, B = 3.0, F = 0.0
    double gradePoints;
    // Character to determine if user wants to enter another class
    char again = 'Y';

    std::cout << "GPA Calculator, enter credits and grade for each class." << std::endl;
    std::cout << "Enter credits (0.1-9.9) followed by the grade ex:(3a , 3 A)." << std::endl;
    std::cout << std::endl;
    // Loop to allow user to enter multiple classes until they choose to stop by entering 'N' or 'n'. (I used ai for this part as i was stuck on how to make a clean loop that allows the user to enter multiple classes without having to restart the program.)
    while (again == 'Y') {
        
        std::cout << "Enter credits and grade: ";
        std::cin >> credits >> grade;
        // Convert grade to uppercase. makes the code insensitive to lowercase input.
        for (int i = 0; i < grade.length(); i++) {
            grade[i] = toupper(grade[i]);
        }
        //check if the input for credits is valid. If not, prompts the user to enter a valid number and continue to the next part of the loop. (I used ai for this part as i was stuck on how to make a clean check if the input is a number or not.)
        if (std::cin.fail()) {
            std::cout << "Invalid credits. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
            continue;
        }
        
        if (credits <= 0) {
            std::cout << "Invalid credits." << std::endl;
            continue;
        }
        else if (credits >= 10) {
            std::cout << "Invalid credits." << std::endl;
            continue;
        }
        //
        if (grade == "A+") {
            gradePoints = 4.0;
        }
        else if (grade == "A") {
            gradePoints = 4.0;
        }
        else if (grade == "A-") {
            gradePoints = 3.7;
        }
        else if (grade == "B+") {
            gradePoints = 3.3;
        }
        else if (grade == "B") {
            gradePoints = 3.0;
        }
        else if (grade == "B-") {
            gradePoints = 2.7;
        }
        else if (grade == "C+") {
            gradePoints = 2.3;
        }
        else if (grade == "C") {
            gradePoints = 2.0;
        }
        else if (grade == "D") {
            gradePoints = 1.0;
        }
        else if (grade == "F") {
            gradePoints = 0.0;
        }
        else if (grade == "WU") {
            gradePoints = 0.0;
        }
        else if (grade == "FIN") {
            gradePoints = 0.0;
        }
        else if (grade == "FAB") {
            gradePoints = 0.0;
        }
        // If the grade input does not match any of the valid letter grades, it will output "Invalid grade." and prompt user to enter a valid grade/value
        else {
            std::cout << "Invalid grade." << std::endl;
            continue;
        }
        // Calculate total points by multiplying credits by grade points and adding to total points. Calculates total credits by adding credits to total credits. Also increases classes taken by 1 for each class entered.
        tp = tp + credits * gradePoints;
        tc = tc + credits;
        classesTaken = classesTaken + 1;

        std::cout << "Do you want to enter grade from another class? Y/N: ";
        std::cin >> again;
        // Convert again to uppercase makes the code insensitive to lowercase input.
        again = toupper(again);

        std::cout << std::endl;
    }
    //becomes invalid if exactly 0 classes are entered. If no classes are entered, the program will output "No classes entered." instead of trying to calculate the GPA and outputting an error message. If at least one class is entered, it will calculate and output the GPA as before.
    if (classesTaken == 0) {
        std::cout << "No classes entered." << std::endl;
    }
    // If at least one class is entered, the program will calculate accordingly.
    else {
        // Calculate GPA by dividing total points by total credits.
        double gpa = tp / tc;
        // rounds to the nearest hundredth. (I used ai for this part as i was stuck on how to round the output to the nearest hundredth. (didnt know what library to use for this))
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Classes taken: " << classesTaken << std::endl;
        std::cout << "Semester GPA: " << gpa << std::endl;
    }

    return 0;
}