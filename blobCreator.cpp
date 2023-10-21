#include <iostream>
#include <fstream>
#include <random>

int main(void)
{
    std::ofstream blobsFile;
    blobsFile.open("randomBlob.txt");
    if(!blobsFile.is_open())
    {
        std::cout << "Couldn't open the file" << std::endl;
        return 1;
    }

    int row = 0;
    int column = 0;

    std::cout << "Enter the row and column with one space: ";
    std::cin >> row >> column; 
    blobsFile << row << " " << column << "\n";
    srand(time(0));
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            if(std::rand() % 2 == 1)
            {
                blobsFile << "x";
            }
            else
            {
                blobsFile << " ";
            }
        }
        blobsFile << "\n";
    }
}