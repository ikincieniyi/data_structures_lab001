#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readCharFromFile(std::ifstream& charFile, char** charArr, int row, int column);
void showBlobs(char** charArr, int row, int column);
void findBlob(char** charArr, int row, int column);
void blob_reshaper(std::vector<std::vector<int>>& blob_info_hld, char** charArr, char blob_id, int row, int column, int row_loc, int column_loc);


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

    readCharFromFile(inputFile, blobs, row, column); //reads the cars from inputFile file and add them into the blobs array

    inputFile.close(); //closing the input file

    showBlobs(blobs, row, column); //shows the blobs with pretty format

    findBlob(blobs, row, column);

    showBlobs(blobs, row, column);

    //releasing the memory
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
    while(std::getline(charFile, blobStr) && rowCounter < row) //reading the file line to line
    {
        for(int i = 0; i < column; i++) //after reading each line carries the chars in that line into to array
        {
            charArr[rowCounter][i] = blobStr[i];
        }
        rowCounter++;
    }

    if(rowCounter < row) //if reads less char from the expected, shows an error
    {
        std::cout << "########################" << std::endl;
        std::cerr << "#File ended prematurely#" << std::endl;
        std::cout << "########################" << std::endl;
        std::cerr << "expected row was: " << row << " but there was " << rowCounter << " row" << std::endl;
    }
}

void addLine(int width) // adds line between line numbers and table
{
    std::cout << " +";
    for(int i = 0; i < width; i++)
    {
        std::cout << "-";
    }
    std::cout << "+ " << std::endl;
}

void addLineNum(int width) // adds line number to the table
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

    addLineNum(column); // adds line number to the table
    addLine(2 * column - 1); // adds line between line numbers and table. it adds 2*column-1 char because I added 1 space between rows.

    for(int i = 0; i < row; i++)
    {
        std::cout << i << "|";
        for(int j = 0; j < column; j++)
        {
            std::cout << charArr[i][j] << " ";
        }
        std::cout << "\b|" << i << std::endl; // '\b' is for erasing the last space after last member of the each row
    }

    addLine(2 * column - 1);
    addLineNum(column);
}

//ascii number of 'A' is 65

void findBlob(char** charArr, int row, int column)
{
    char blob_id = 65;
    std::vector<std::vector<std::vector<int>>> blob_info;
    std::vector<std::vector<int>> blob_info_holder;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            if(charArr[i][j] == 'x')
            {
                blob_id++;
                blob_info_holder.clear();
                blob_reshaper(blob_info_holder, charArr, blob_id, row, column, i, j);
                blob_info.push_back(blob_info_holder);
            }
        }
    }
    std::cout << blob_info.size();
    std::cout << blob_info_holder.size() << std::endl;
}

void blob_reshaper(std::vector<std::vector<int>>& blob_info_hld, char** charArr, char blob_id, int row, int column, int row_loc, int column_loc)
{
    if(row_loc < 0 || column_loc < 0 || row_loc >= row || column_loc >= column || charArr[row_loc][column_loc] != 'x')
    {
        return;
    }

    blob_info_hld.push_back({row_loc, column_loc});
    charArr[row_loc][column_loc] = blob_id;
    
    int moves[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for(int i = 0; i < 4; i++)
    {
        blob_reshaper(blob_info_hld, charArr, blob_id, row, column, row_loc + moves[i][0], column_loc + moves[i][1]);
    }
}