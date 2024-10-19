#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{0, 1, -1}, {-3, 7,0}, {-2, 1,0}};

    std::cout << mat << std::endl;
    std::cout << gaussian_elimination(mat) << std::endl;
    std::cout << mat.det() << std::endl;
}