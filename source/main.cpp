#include <matrix.h>
#include <iostream>

int main() {
    linalg::Matrix mat1 = {{10, 1}, {20, 2}, {30, 3}};
    linalg::Matrix mat2 = {101, 202, 303};
    mat1.print();
    mat2.print();
}