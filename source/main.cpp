#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat1 = {{10, 1}, {20, 2}, {30, 3}};
    linalg::Matrix mat2 = {{100, 10, 200}, {20, 300, 30}};
    linalg::Matrix mat3 = {{100, 10}, {200, 20}, {300, 30}};

    std::cout << mat1 * 0.0001;
    std::cout << mat2;
    std::cout << mat3 * (-1);
}