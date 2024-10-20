#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{1, -1, 7}, {10, -3, 0}, {-2, 1, 5}};
    //linalg::Matrix mat = {{5, -1, 8}, {41, -43, 1}, {0, -5, 79}};
    //linalg::Matrix mat = {{-55, 3, 7}, {0, 2, 0}, {6, 11, -98}};
    //linalg::Matrix identity_matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    for (int deg = 0; deg < 5; ++deg) {
        std::cout << linalg::power(mat, deg) << std::endl;
    }
}