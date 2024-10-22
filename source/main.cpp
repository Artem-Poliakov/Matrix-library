#include <matrix.h>
#include <iostream>

int main() {
    const linalg::Matrix mat1 = {{1, 0, 8}, {9, -4, 9}, {1, -5, 0}};
    linalg::Matrix mat2 = {{-5, 1, 7}, {2, -7, 1}, {-3, -5, 9}};

    std::cout << mat1[0][0] << std::endl;
    std::cout << mat2[0][0] << std::endl;
//  std::cout << (mat1[0][0] = 0) << std::endl; // forbidden 
    std::cout << (mat2[0][0] = 0) << std::endl;
    std::cout << mat1 << std::endl;
    std::cout << mat2 << std::endl;
}