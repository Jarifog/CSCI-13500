#include <iostream> 


int SumTwoNumbers(int& first_num, int second_num);
void PrintDone(int sum_result);

int main(){

    const int result = 25;
    std::cout << result << std::endl; 
    std::cout << SumTwoNumbers(result, 3) << std::endl;
    std::cout << result << std::endl;


}

int SumTwoNumbers(const int& first_num, int second_num){
    first_num = 3000;
    int result = first_num + second_num;

    return result;
}

