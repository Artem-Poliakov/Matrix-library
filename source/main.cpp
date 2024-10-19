#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat = {{10, 1, 10}, {20, 2, 20}, {30, 3, 30}};

    std::cout << "Trace(mat) = " << mat.trace() << std::endl;
    std::cout << "Norm(mat) = " << mat.norm() << std::endl;
}