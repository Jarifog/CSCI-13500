#include <iostream>
using namespace std;

int main(){
    int a;
    int b;
    char operation;

    cout << "enter first digits";
    cin >> a;

    cout << "enter second digits";
    cin >> b;
 
    cout << "Pick a symbol: (+, -, *, /, %): ";
    cin >> operation;

    switch(operation) {
        case '+':
            cout << "Result :" << a + b << endl;
            break;
        
        case '-':
             cout << "Result :" << a - b << endl;
            break;

        case '*':
            cout << "Result :" << a * b << endl;
            break;
        
        case '/':
            if (b == 0) {cout<< "error: number cannot be divded by 0"<< endl;}
             cout << "Result :" << a / b << endl;
            break;
        case '%':
            if (b == 0) {cout<< "error: number cannot be moduled by 0"<< endl;}
             cout << "Result :" << a % b << endl;
            break;
        
        default: cout << "invalid operation please enter a valid input" <<endl;
     

    }
    return 0;
}