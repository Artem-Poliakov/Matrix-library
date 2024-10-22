#include <matrix.h>
#include <tests.h>

int main() {
    linalg_tests::construction_test();
    linalg_tests::printing_test();
    linalg_tests::assignment_test();
    linalg_tests::arithmetic_test();
}