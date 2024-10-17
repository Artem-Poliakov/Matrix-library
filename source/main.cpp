#include <matrix.h>
#include <iostream>
#include <typeinfo>

int main() {
    linalg::Matrix mat1 = {{10, 1}, {20, 2}, {30, 3}};
    linalg::Matrix mat2 = {{100, 10, 200}, {20, 300, 30}};
    linalg::Matrix mat3 = {{100, 10}, {200, 20}, {300, 30}};

    (mat1 * mat2).print();
    (mat1 + mat3).print();
    (mat1 - mat3).print();
    (6.66 * mat1).print();
    (mat1 * 7.77).print();

    mat1 *= mat2;
    mat1.print();
    mat1 *= 5.55;
    mat1.print();
}