#include <tests.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define TESTS_NO 10

size_t rand_size(size_t from, size_t to) {
    std::srand(time(NULL));
    return static_cast<size_t>(std::rand() % (to - from + 1) + from);
}

linalg::Matrix rand_matrix(size_t rows, size_t cols, bool integer = false) {
    std::srand(time(NULL));
    linalg::Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (integer) { result(i, j) = (int)(std::rand() - RAND_MAX / 2); }
            else { result(i, j) = (double) (std::rand() - RAND_MAX / 2) / RAND_MAX; }
        }
    }
    return result;
}

void test_report(const char* test_name) {
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~ " << test_name << " completed ~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
}

//>>>>>>>>>>>>>>
//TESTS
//>>>>>>>>>>>>>>

void linalg_tests::construction_test() {
    try {
        linalg::Matrix m0;
        linalg::Matrix m1(4);
        linalg::Matrix m2(4, 6);
        linalg::Matrix m3(m1);
        linalg::Matrix m4(std::move(m2));
        linalg::Matrix m5 = { {1, 2, 3}, {4, 5, 6} };
        linalg::Matrix m6 = { {1, 2, 3, 4, 5, 6} };
        linalg::Matrix m7 = { 1, 2, 3, 4, 5, 6 };
        //linalg::Matrix m8 = { {1},{2},{3},{4},{5},{6} };
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("construction_test");
}

void linalg_tests::printing_test() {
    try {
        std::cout << linalg::Matrix{} << std::endl;
        std::cout << rand_matrix(1, 1) << std::endl;
        std::cout << rand_matrix(1, 3) << std::endl;
        std::cout << rand_matrix(3, 1) << std::endl;
        size_t m = rand_size(2, 5), n = rand_size(2, 5);
        std::cout << rand_matrix(m, n, true) << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("printing_test");
}

void linalg_tests::assignment_test() {
    try {
        linalg::Matrix m1, m2;
        m1 = linalg::Matrix{ 1, 2, 3, 4, 5, 6 };
        m2 = m1;

        linalg::Matrix m = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
        double val = m(0,2);
        m(0,2) = 7.0;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("assignment_test");
}

void linalg_tests::arithmetic_test() {
    try {
        for (size_t i = 0; i < TESTS_NO; ++i)
        {
            size_t n = rand_size(1, 10);
            linalg::Matrix A = rand_matrix(n, n);
            std::cout << (A + A == 2 * A);
            std::cout << (A + A == A * 2);
            std::cout << (A - A == linalg::zeros_matrix(n, n));
            std::cout << (A + (- A) == linalg::zeros_matrix(n, n));
            std::cout << (A * A == linalg::power(A, 2));
            std::cout << (A * linalg::inverse(A) == linalg::identity_matrix(n));
            std::cout << (A * linalg::identity_matrix(n) == A);
            std::cout << (linalg::power(linalg::inverse(A), 3) == linalg::power(A, -3));
            std::cout << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("arithmetic_test");
}