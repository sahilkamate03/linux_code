#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Create an empty string
    std::string result;

    // Loop through the vector and add each integer to the string
    for (int i=1; i<numbers.size(); i++) {
        // Convert the integer to its string representation and concatenate it
        result += std::to_string(numbers[i]);
    }

    // Print the resulting string
    std::cout << result << std::endl;

    return 0;
}
