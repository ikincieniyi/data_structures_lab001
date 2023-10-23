#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


void readCharFromFile(std::ifstream& charFile, char** charArr, int row, int column);
void showBlobs(char** charArr, int row, int column);
void findBlob(std::vector<std::vector<std::vector<int>>>& blob_info, char** charArr, int row, int column);
void blob_reshaper(std::vector<std::vector<int>>& blob_info_hld, char** charArr, char blob_id, int row, int column, int row_loc, int column_loc);
void showBlobInfo(const std::vector<std::vector<std::vector<int>>>& blob_info);


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

    std::vector<std::vector<std::vector<int>>> blob_info; //this vector stores the every blob info
    findBlob(blob_info, blobs, row, column); //finds the blobs and stores them into the blob_info

    showBlobInfo(blob_info);//shows the The blob number, the number of pixels making up the blob, and its 
    //center of mass (CoM) in the y and x coordinates, that is, CoM Row and CoM Column

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
    std::cout << "\n\n";
    addLineNum(column); // adds line number to the table
    addLine(2 * column - 1); // adds line between line numbers and table. it adds 2*column-1 char because I added 1 space between rows.

    for(int i = 0; i < row; i++)
    {
        std::cout << i % 10 << "|";
        for(int j = 0; j < column; j++)
        {
            std::cout << charArr[i][j] << " ";
        }
        std::cout << "\b|" << i % 10 << std::endl; // '\b' is for erasing the last space after last member of the each row
    }

    addLine(2 * column - 1);
    addLineNum(column);
    std::cout << "\n\n";
}

//ascii number of 'A' is 65

void findBlob(std::vector<std::vector<std::vector<int>>>& blob_info, char** charArr, int row, int column)
{
    char blob_id = 32; //32 is ascii number of space(" ")
    std::vector<std::vector<int>> blob_info_holder; //carries the every blob info into the blob_info vector
    for(int i = 0; i < row; i++) //looking for every index
    {
        for(int j = 0; j < column; j++)
        {
            if(charArr[i][j] == 'x') //if that index has x that means this is a new blob and we will look for other members
            {
                blob_info_holder.clear(); //clears the vector for the new inputs
                blob_reshaper(blob_info_holder, charArr, blob_id, row, column, i, j); //looks for other blob pixels and
                                                                                      //stores them in the blob_info_holder
                blob_info.push_back(blob_info_holder); //adds the new blob's info to the blob_info as a new blob
                //blob_id++; //we can use this if we want to see the visual result. but it just works with small inputs
            }
        }
    }
}

void blob_reshaper(std::vector<std::vector<int>>& blob_info_hld, char** charArr, char blob_id, int row, int column, int row_loc, int column_loc)
{
    if(row_loc < 0 || column_loc < 0 || row_loc >= row || column_loc >= column || charArr[row_loc][column_loc] != 'x')
    {
        return; //if we are out of the boundaries it returns back
    }

    blob_info_hld.push_back({row_loc, column_loc}); //stores the coordinates of pixel of blobs
    charArr[row_loc][column_loc] = blob_id; //changes the x with blob_id(currently space) so it will be marked and we wont read that again
    
    int moves[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; //looking for right, left, down and up
    for(int i = 0; i < 4; i++)
    {
        blob_reshaper(blob_info_hld, charArr, blob_id, row, column, row_loc + moves[i][0], column_loc + moves[i][1]);
    }
}

int sumVector(std::vector<std::vector<int>> vect, int index)
{
    int sum = 0;
    for(int i = 0; i < vect.size(); i++) //sums the numbers that are in the same index
    {
        sum += vect.at(i).at(index);
    }
    return sum;
}
void showBlobInfo(const std::vector<std::vector<std::vector<int>>>& blob_info)
{
    std::cout << "+------+------------+---------+------------+" << std::endl; //+6+12+9+12+ line format
    /*std::cout << "|" << std::setw(6) << "BLOB" << "|" << std::setw(12) << "NoOfPixels" << "|";
    std::cout << std::setw(9) << "CoM Row" << "|" << std::setw(6) << "CoM Column" << "|" << std::endl; */
    std::cout << "+ BLOB + NoOfPixels + CoM Row + CoM Column +" << std::endl;
    std::cout << "+------+------------+---------+------------+" << std::endl;
    for(int i = 0; i < blob_info.size(); i++)
    {
        int NoOfPixels = blob_info.at(i).size();
        float CoM_Row = float(sumVector(blob_info.at(i), 0)) / NoOfPixels;
        float CoM_Column = float(sumVector(blob_info.at(i), 1)) / NoOfPixels;

        std::cout << std::showpoint << std::fixed << std::setprecision(2);
        std::cout << "|" << std::setw(6) << i + 1 << "|" << std::right << std::setw(12) << NoOfPixels << "|";
        std::cout << std::setw(9) << CoM_Row << "|" << std::setw(12) << CoM_Column << "|" << std::endl;
    }
    std::cout << "+------+------------+---------+------------+" << std::endl;
}
