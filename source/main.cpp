#include <matrix.h>
#include <iostream>
#include <typeinfo>

int main() {
    linalg::Matrix mat = {{10, 1}, {20, 2}, {30, 3}};
    mat.print();
    mat.reshape(2, 3);
    mat.print();
}