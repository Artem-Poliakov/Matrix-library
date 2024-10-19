#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{0, 1, -1, 7}, {10, -3, 7, 0}, {-2, 1, 0, 45}, {3, 57, -8, 11}};

    std::cout << mat << std::endl;
    std::cout << minor(mat, 1, 2);
}