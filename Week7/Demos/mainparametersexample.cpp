#include <iostream>

int main(int argc, char* argv[]){

    std::cout << "There are " << argc << " elements passed." << std::endl;
    std::cout << "First row holds "  << argv[1] << std::endl;

    return 0;

}