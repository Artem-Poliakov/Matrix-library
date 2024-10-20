#include <matrix.h>
#include <iostream>

int main() {
    //linalg::Matrix mat = {{1, -1, 7}, {10, -3, 0}, {-2, 1, 45}};
    //linalg::Matrix mat = {{5, -1, 8}, {41, -43, 1}, {0, -5, 79}};
    linalg::Matrix mat = {{-55, 3, 7}, {0, 2, 0}, {6, 11, -98}};
    linalg::Matrix inv = inverse(mat);

    std::cout << mat << std::endl;
    std::cout << "multiply by\n" << std::endl;
    std::cout << inv << std::endl;
    std::cout << "equals\n" << std::endl;
    std::cout << mat * inv << std::endl;
}