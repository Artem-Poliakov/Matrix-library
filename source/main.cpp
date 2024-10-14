#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat1(5, 10);
    linalg::Matrix mat2;
    mat2 = mat1;

    linalg::Matrix mat3;
    mat3 = std::move(mat1);

    std::cout << "mat1.empty(): " << mat1.empty() << '\n';
    std::cout << "mat2.empty(): " << mat2.empty() << '\n';
    std::cout << "mat3.empty(): " << mat3.empty() << '\n';
}