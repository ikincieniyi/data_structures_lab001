#include <iostream>
#include <fstream>
#include <string>

void readCharFromFile(std::ifstream& charFile, char** charArr, int row, int column);
void showBlobs(char** charArr, int row, int column);

int main(void)
{
    std::string fileName;
    std::cout << "Enter the file name: ";
    std::cin >> fileName;
    
    std::ifstream inputFile;
    inputFile.open(fileName);
    if(!inputFile.is_open())
    {
        std::cout << "Couldn't open inputFile" << std::endl;
    }
    
    int row = 0;
    int column = 0;

    inputFile >> row >> column;
    inputFile.ignore(); //ignoring the end line character(\n)

    //creating a 2d dynamic array for storing the input
    char** blobs = new char*[row];
    for(int i = 0; i < row; i++)
    {
        blobs[i] = new char[column];
    }

    readCharFromFile(inputFile, blobs, row, column);
/*     //reading the input from the file
    std::string blobStr; //this string will carry the data from given file to the blobs array
    int rowCounter = 0;
    while(std::getline(inputFile, blobStr) && rowCounter < row)
    {
        for(int i = 0; i < column; i++)
        {
            blobs[rowCounter][i] = blobStr[i];
        }
        rowCounter++;
    } */
    
    inputFile.close(); //closing the input file

    showBlobs(blobs, row, column);

/*     for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            std::cout << blobs[i][j] << " ";
        }
        std::cout << std::endl;
    } */
    
    for(int i = 0; i < row; i++)
    {
        delete[] blobs[i];
    }
    delete[] blobs;

}

void readCharFromFile(std::ifstream& charFile, char** charArr, int row, int column)
{
    //reading the input from the file
    std::string blobStr; //this string will carry the data from given file to the blobs array
    int rowCounter = 0;
    while(std::getline(charFile, blobStr) && rowCounter < row)
    {
        for(int i = 0; i < column; i++)
        {
            charArr[rowCounter][i] = blobStr[i];
        }
        rowCounter++;
    }

    if(rowCounter < row)
    {
        std::cerr << "File ended prematurely" << std::endl;
    }
}

void addLine(int width)
{
    std::cout << " +";
    for(int i = 0; i < width; i++)
    {
        std::cout << "-";
    }
    std::cout << "+ " << std::endl;
}

void addLineNum(int width)
{
    std::cout << "  "; //2blank space for the table design
    for(int i = 0; i < width; i++)
    {
        std::cout << i % 10 << " "; //printing the last digit of column number so it can only took 1 space
    }
    std::cout << std::endl;
}

void showBlobs(char** charArr, int row, int column)
{
    addLineNum(column);
    addLine(2 * column - 1);

    for(int i = 0; i < row; i++)
    {
        std::cout << i << "|";
        for(int j = 0; j < column; j++)
        {
            std::cout << charArr[i][j] << " ";
        }
        std::cout << "\b|" << i << std::endl;
    }

    addLine(2 * column - 1);
    addLineNum(column);
}
