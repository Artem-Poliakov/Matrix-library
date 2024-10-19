#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{24, 1, 11, 44}, {10, 7, 0, 78}, {3, 16, 45, 19}};

    std::cout << gaussian_elimination(mat) << std::endl;
    std::cout << mat << std::endl;
}