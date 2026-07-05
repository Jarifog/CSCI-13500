#include <iostream>
#include <vector>

 bool checkValid(std::vector<std::vector<int>>& matrix) {
        int matrix_size = matrix.size();

        // Check each row
        for (int i = 0; i < matrix_size; i++) {
            
            std::vector<bool> seen(matrix_size + 1, false);

            for (int j = 0; j < matrix_size; j++) {
                int current_value= matrix[i][j];
                if (current_value< 1 || current_value> matrix_size|| seen[current_value]) {
                    return false;
                }
                seen[current_value] = true;
            }
        }

        // Check each column
        for (int j = 0; j < matrix_size; j++) {
            
            std::vector<bool> seen(matrix_size + 1, false);

            for (int i = 0; i < matrix_size; i++) {
                int current_value= matrix[i][j];
                if (current_value< 1 || current_value> matrix_size|| seen[current_value]) {
                    return false;
                }
                seen[current_value] = true;
            }
        }

        return true;
    }

    int main(){
        std::vector<std::vector<int>> matrix = {
            {1, 2, 3},
            {3, 1, 2},
            {2, 3, 1}
        };
        std::cout << checkValid(matrix) << std::endl;
    }