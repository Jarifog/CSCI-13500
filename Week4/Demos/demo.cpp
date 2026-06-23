
#include <iostream>
#include <vector>

//Leetcode Link: https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/description/

int main()
{
    std::vector<std::vector<int>> grid = {
    { 4,  3,  2, -1}, // 0
    { 3,  2,  1, -1}, // 1
    { 1,  1, -1, -2}, // 2
    {-1, -1, -2, -3} // 3
    };

    int num_rows = grid.size(); // 4
    int num_col = grid[0].size(); // 4

    int row = num_rows - 1;
    int col = 0;
    int negative_counter = 0;

    while (row >= 0 && col < num_col){
        if (grid[row][col] < 0){
            negative_counter += (num_col - col);
            row--;
        }
        else{
            col++;
        }
    }

    std::cout << "Count: " << negative_counter << std::endl; 

    return 0;
}