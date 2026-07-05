# Pointer Detective
Welcome to the agency detective. We ran into a couple of tough cases, and we need your help. As the best pointer detective in town, we thought of you first. 

## Introduction

A mysterious bug has appeared in several C++ programs. Your job as a **Pointer Detective** is to investigate each program and determine what is happening behind the scenes.

For **each mystery**, complete the following tasks **before running the program**:

1. Predict the program's output.
2. Explain **why** the output occurs.
3. Draw the call stack while the function executes.
4. Identify whether the function uses:
   - Pass by Copy
   - Pass by Reference
   - Pass by Pointer

After completing your predictions, compile and run the program to verify your answers.

---

# Mystery #1 – The Copycat

**Concepts:** Pass by Copy, Scope, Call Stack

```cpp
#include <iostream>

void addFive(int number)
{
    number += 5;
    std::cout << "Inside addFive(): " << number << std::endl;
}

int main()
{
    int value = 10;

    addFive(value);

    std::cout << "In main(): " << value << std::endl;
}
```

### Questions

1. What is the output of this program?
2. Why doesn't `value` change after calling `addFive()`?
3. Where does the variable `number` exist?
4. Draw the call stack while `addFive()` is executing.
5. What happens to `number` after the function returns?

---

# Mystery #2 – The Mirror

**Concepts:** References, `const`, Modifying Variables

```cpp
#include <iostream>

void investigate(int& suspect, const int& clue)
{
    suspect += clue;

    std::cout << "Inside investigate(): "
         << suspect << " " << clue << std::endl;
}

int main()
{
    int score = 10;
    int bonus = 5;

    investigate(score, bonus);

    std::cout << score << " " << bonus << std::endl;
}
```

### Questions

1. What is the output of this program?
2. Why does `score` change while `bonus` does not?
3. Why is `clue` declared as a `const` reference?
4. What would happen if the function attempted to modify `clue`?
5. Draw the call stack while `investigate()` is executing.

---

# Mystery #3 – Following the Pointer

**Concepts:** Raw Pointers, Dereferencing, `nullptr`

```cpp
#include <iostream>

void investigate(int* evidence)
{
    if (evidence != nullptr)
    {
        *evidence *= 2;
    }
}

int main()
{
    int clue = 7;

    investigate(&clue);

    std::cout << clue << std::endl;
}
```

### Questions

1. What is the output of this program?
2. Why do we pass `&clue` instead of `clue`?
3. What does `*evidence` do?
4. Why is the `nullptr` check important?
5. What would happen if the function was called as `investigate(nullptr);`?
6. Draw the call stack while `investigate()` is executing.

---

# Mystery #4 – The Master Case

**Concepts:** Pass by Copy, Pass by Reference, Pass by Pointer, Return Values

```cpp
#include <iostream>

int mysteryA(int x)
{
    x += 10;
    return x;
}

void mysteryB(int& y)
{
    y *= 2;
}

void mysteryC(int* z)
{
    if (z != nullptr)
    {
        (*z)--;
    }
}

int main()
{
    int value = 5;

    value = mysteryA(value);
    mysteryB(value);
    mysteryC(&value);

    std::cout << value << std::endl;
}
```

### Questions

1. Predict the output of the program.
2. Draw the call stack after each function call.
3. Which function uses:
   - Pass by Copy?
   - Pass by Reference?
   - Pass by Pointer?
4. Which functions modify the original variable?
5. Why does `mysteryA()` return a value, while `mysteryB()` and `mysteryC()` do not?
6. Which approach would you choose if your goal was to modify the original variable? Explain your reasoning.

---

# Reflection

Answer the following questions in complete sentences.

1. What is the difference between passing a variable by copy, by reference, and by pointer?
2. When would you choose to use a reference instead of a pointer?
3. Why might a function accept a pointer instead of a reference?
4. What role does the `const` keyword play when working with references and pointers?
5. How does understanding the call stack help explain why variables change—or do not change—during function calls?