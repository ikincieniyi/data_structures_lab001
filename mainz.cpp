#include <iostream>
#include <fstream>
#include <string>


int main(void)
{
    std::ifstream inputFile;
    inputFile.open("blobs1.txt");
    if(!inputFile.is_open())
    {
        std::cout << "Couldn't open inputFile" << std::endl;
    }
    
    int row = 0;
    int column = 0;

    inputFile >> row;
    inputFile >> column;
    inputFile.ignore();

    //std::cout << "row: " << row << ", column: " << column << std::endl;

    char** blobs = new char*[row];
    for(int i = 0; i < row; i++)
    {
        blobs[i] = new char[column];
    }

    std::string blobStr; //this char array will carry the data from given file to the blobs array
    int rowCounter = 0;
    while(std::getline(inputFile, blobStr))
    {
        for(int i = 0; i < column; i++)
        {
            blobs[rowCounter][i] = blobStr[i];
        }
        rowCounter++;
    }



    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            std::cout << blobs[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    for(int i = 0; i < row; i++)
    {
        delete[] blobs[i];
    }
    delete[] blobs;

}