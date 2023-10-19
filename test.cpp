#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    /* std::vector<std::vector<std::vector<char>>> arr;
    std::vector<std::vector<char>> arr1;
    arr1.push_back({'a', 'b'});

    arr.push_back(arr1);
    std::cout << arr[0][0][0]; */

    std::cout << "+------+------------+---------+------------+" << std::endl; //+6+12+9+12+ line format
    std::cout << "|" << std::left << std::setw(6) << "BLOB" << "|" << std::right << std::setw(12) << "NoOfPixels" << "|";
    std::cout << std::setw(9) << "CoM Row" << "|" << std::setw(12) << "CoM Column" << "|" << std::endl;
}
