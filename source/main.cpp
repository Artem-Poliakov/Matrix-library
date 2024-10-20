#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{5, -1, 8}, {4, -43, 1}, {0, -5, 9}};

    std::cout << ( linalg::power(mat, -3) == linalg::inverse(linalg::power(mat, 3)) );
}