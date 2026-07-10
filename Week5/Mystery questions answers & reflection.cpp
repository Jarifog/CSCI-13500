

Question #1
 1. What is the output of this program? 

Inside addFive(): 15
 In main(): 10 

2. Why doesn't the value change after calling addFive()?

Missing the & and therefore a copy of this number is not able to make changes as it requires the actual value/variable. 

 3. Where does the variable number exist? 

Inside addFive()

4. Draw the call stack while addFive() is executing. 

Add five() goes at the top of the call stack after main. 

5. What happens to number after the function returns 

It does not exist anymore as it is outside of the scope. 

Question 2

What is the output of this program?

Inside investigate(): 15 5
15 5

Why does score change while bonus does not?


Score change is passed by reference due to the & clue does not change as there is a const attached before it meaning that it overrides the &.  

Why is clue declared as a const reference?

To disallow changes to it. 

What would happen if the function attempted to modify clue?

Compiler error. 

Draw the call stack while investigate() is executing.


Investigate function goes on the top while main is at the bottom. 


Question 3 

What is the output of this program?
14

Why do we pass &clue instead of clue?

The function expects the pointer int* and requires a memory address which is defined by the &

What does *evidence do?

Dereferences the pointer and accesses the actual value. 

Why is the nullptr check important?

To allow the program to prevent the program from dereferencing null pointers. 

What would happen if the function was called as investigate(nullptr);?

It will do nothing and run due to the nullptr being set via condition: if (evidence != nullptr)

Draw the call stack while investigate() is executing.
Investigate(int* evidence) on top then main at the bottom of the stack. 




Question 4

Predict the output of the program.

 29. 

Draw the call stack after each function call.

Which function uses:
Pass by Copy? : mysteryA(int x) 
Pass by Reference?: mysteryB(int& y) 
Pass by Pointer?: mysteryC(int* z) 

Which functions modify the original variable?
Mystery B and C as they use pass by reference and pass by pointer via: int& y and int* z

Why does mysteryA() return a value, while mysteryB() and mysteryC() do not?
Mystery A uses pass by copy which does not allow modifications whereas B and c use pass by reference which allows modification to the original. 

Which approach would you choose if your goal was to modify the original variable? Explain your reasoning.

Easily pass by reference as it directly modifies and does the changes to the original variable. Does not require much modification to the original code other than adding &. 












Reflection: 

What is the difference between passing a variable by copy, by reference, and by pointer?

Pass by copy creates a copy of the original variable and changes to this does not affect the original variable. Whereas pass by reference and pass by pointer directly goes to the actual variable and allows for modifications this is done via & for pass by reference and dereferencing for pointer. 

When would you choose to use a reference instead of a pointer?

Reference is much easier to use, understand and handle as it simply uses & to modify variables/values. 

Why might a function accept a pointer instead of a reference?

When the variable is nullptr, and allows for validation to check if address is valid or not. 

What role does the const keyword play when working with references and pointers?

Prevents a value or variable to be modified if required. 

How does understanding the call stack help explain why variables change—or do not change—during function calls?

Allows the user to know when the function ends and when it is executed. Also helps keep track of pass by copy disappearing after the function ends where as the pointers and references can still modify the original variables in main()

