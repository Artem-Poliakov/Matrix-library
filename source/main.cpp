#include <matrix.h>
#include <iostream>

int main() {
    //linalg::Matrix mat = {{0, 1, -1, 7}, {10, -3, 7, 0}, {-2, 1, 0, 45}};
    linalg::Matrix mat = {{0, 1, -1, 7, 10, -3, 7, 0, -2, 1, 0, 45}};

    std::cout << "transpose\n" << std::endl;
    std::cout << mat << std::endl;
    std::cout << "     | |   \n" << std::endl;
    std::cout << transpose(mat) << std::endl;
}