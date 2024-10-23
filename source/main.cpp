#include <tests.h>

int main() {
    linalg_tests::construction_test();
    linalg_tests::printing_test();
    linalg_tests::assignment_test();
    linalg_tests::reshape_test();
    linalg_tests::arithmetics_test();
    linalg_tests::linear_algebra_test();
    linalg_tests::gauss_test();
}