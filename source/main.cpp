#include <matrix.h>
#include <tests.h>
#include <iostream>

int main() {
    //linalg_tests::construction_test();
    //linalg_tests::printing_test();

    linalg::Matrix A = {{1, 2}, {3, 4}};
    std::cout << -A << std::endl;
}