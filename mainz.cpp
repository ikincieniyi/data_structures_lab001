#include <iostream>
#include <fstream>


int main(void)
{
    std::ifstream inputFile;
    inputFile.open("blobs1.txt");
    if(!inputFile.is_open())
    {
        std::cout << "Couldn't open inputFile" << std::endl;
    }
}