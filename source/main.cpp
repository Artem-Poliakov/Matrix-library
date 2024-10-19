#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{10, 1}, {20, 2}, {30, 3}};
    linalg::Matrix mat1 = {{10, 1}, {20, 2}, {30, 3}};
    linalg::Matrix mat2 = mat1 + 0.0001 * mat1;
    linalg::Matrix mat3 = mat1 + 0.00000001 * mat1;

    std::cout << "Mat1 == Mat: " << (mat == mat1) << std::endl;
    std::cout << "Mat2 == Mat: " << (mat == mat2) << std::endl;
    std::cout << "Mat3 == Mat: " << (mat == mat3) << std::endl;
    std::cout << '\n';
    std::cout << "Mat1 != Mat: " << (mat != mat1) << std::endl;
    std::cout << "Mat2 != Mat: " << (mat != mat2) << std::endl;
    std::cout << "Mat3 != Mat: " << (mat != mat3) << std::endl;
}