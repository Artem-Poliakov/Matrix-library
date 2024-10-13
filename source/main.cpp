#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat1(5, 10);
    linalg::Matrix mat2;
    mat2 = mat1;
    std::cout << "Mat1: " << mat1.rows() << ' ' << mat1.columns() << '\n';
    std::cout << "Mat2: " << mat2.rows() << ' ' << mat2.columns() << '\n';

    linalg::Matrix mat3;
    mat3 = std::move(mat1);
    std::cout << "Mat1: " << mat1.rows() << ' ' << mat1.columns() << '\n';
    std::cout << "Mat3: " << mat3.rows() << ' ' << mat3.columns() << '\n';
}