#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{1, -1, 0}, {2, -3, 7}, {9, -4, 0}};
    linalg::Matrix mat0 = {{5, -1, 8}, {41, -43, 1}, {0, -5, 79}};

    std::cout << mat << std::endl;
    std::cout << mat * mat << std::endl;
    std::cout << (mat *= mat) << std::endl;
    std::cout << mat << std::endl;
}