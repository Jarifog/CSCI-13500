#include <iostream>
#include <vector>
#include <string> //used/added string since we are using string in anagram function. 

void removeCopies(std::vector<int>& data){
    
    int uniqueCount = 1;
    //for loop goes through vector once thereofre O(n) time complexity.
    for (int i = 1; i < data.size(); i++) {
        if (data[i] != data[i - 1]) {
            data[uniqueCount] = data[i];
            uniqueCount++;
        }
    }

    data.resize(uniqueCount);
} 

// time complextiy below is O(n) since we are looping through the string once, and rule of thumb it is not a nested loop. 
void isAnagram(std::string officer_name, std::string spy_name) {
// AI assistance note: I used AI to help me understand and implement this anagram-checking method. The idea is to count each letter in the officer name and subtract each letter in the spy name using a vector of size 26.

    std::vector<int> letters(26, 0);

    for (int i = 0; i < officer_name.length(); i++) {
        letters[officer_name[i] - 'a']++;
    }

    for (int i = 0; i < spy_name.length(); i++) {
        letters[spy_name[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (letters[i] != 0) {
            std::cout << "IMPOSTER! IMPOSTER!" << std::endl;
            return;
        }
    }

    std::cout << "No imposter detected!" << std::endl;
}

int main(){

    /*Use other test cases to make sure you program works*/
    std::vector<int> server = {1,1,2,2,2,3,3,4,5,6,6,6};
    

    /*Print out the original server vector before function called*/
     for (auto data : server){
        std::cout << data << " "; // 1,1,2,2,2,3,3,4,5,6,6,6
    }

    std::cout << std::endl;

    removeCopies(server);
    
    /*Print out the modification of the server vector after function called*/
    for (auto data : server){
        std::cout << data << " ";
    }

    std::cout << std::endl;

    /****************************TEST ANAGRAM*************************************/

    isAnagram("syeda", "aysed"); // No imposter detected!
    isAnagram("angelo", "annabeth"); // IMPOSTER! IMPOSTER!

    return 0;

}
