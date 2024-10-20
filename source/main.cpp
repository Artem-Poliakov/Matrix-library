#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat1 = {{0, 1, -1, 7}, {10, -3, 7, 0}, {-2, 1, 0, 45}, {3, 57, -8, 11}};
    linalg::Matrix mat2 = {1, 2, 3, 4};

    std::cout << mat1 << std::endl;
    std::cout << "concatenate\n" << std::endl;
    std::cout << mat2 << std::endl;
    std::cout << "     | |   \n" << std::endl;
    std::cout << concatenate(mat1, mat2) << std::endl;
}