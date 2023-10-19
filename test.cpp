#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile;
    inputFile.open("input.txt"); // Replace "input.txt" with the name of your input file

    if (!inputFile.is_open()) {
        std::cerr << "Couldn't open the input file." << std::endl;
        return 1;
    }

    int rows, cols;
    inputFile >> rows >> cols;
    inputFile.ignore(); // Consume the newline character

    char** array = new char*[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new char[cols];
    }

    // Read the array elements from the file using getline
    for (int i = 0; i < rows; i++) {
        std::string line;
        std::getline(inputFile, line);
        for (int j = 0; j < cols; j++) {
            array[i][j] = line[j];
        }
    }

    // Close the file
    inputFile.close();

    // Now you have the 2D array in 'array'. You can access and manipulate it as needed.

    // Display the array as an example
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << array[i][j];
        }
        std::cout << std::endl;
    }

    // Don't forget to deallocate memory to avoid memory leaks
    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}
