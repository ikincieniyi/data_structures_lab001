#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<std::vector<char>>> arr;
    std::vector<std::vector<char>> arr1;
    arr1.push_back({'a', 'b'});

    arr.push_back(arr1);
    std::cout << arr[0][0][0];
}