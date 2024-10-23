#include <tests.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

#define TESTS_NO 10
#define ACCURACY std::pow(10, -8)

size_t rand_size(size_t from, size_t to) {
    return static_cast<size_t>(std::rand() % (to - from + 1) + from);
}

linalg::Matrix rand_matrix(size_t rows, size_t cols, bool integer = false) {
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
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("construction_test");
}

void linalg_tests::assignment_test() {
    try {
        linalg::Matrix m1, m2;
        m1 = linalg::Matrix{ 1, 2, 3, 4, 5, 6 };
        m2 = m1;

        linalg::Matrix m = { {1, 2, 3}, {4, 5, 6} };
        m(0,0) = 7;
        m[0][0] = 8;

        // RAISING ERROR
        m(100, 100);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "   WORKED" <<  std::endl;
    }
    test_report("assignment_test");
}

void linalg_tests::reshape_test() {
    try {
        size_t k = rand_size(1, 6), l = rand_size(1, 6);
        linalg::Matrix mat = rand_matrix(k, l, true), column = rand_matrix(k, 1, true);
        linalg::Matrix result = linalg::concatenate(mat, column);
        std::cout << mat << "---concatenate---\n" << column << "---turns to---\n" << result << std::endl;

        for (size_t i = 0; i < TESTS_NO; ++i) {
            size_t m = rand_size(1, 10), n = rand_size(1, 10);
            linalg::Matrix M(m, n), Q(n, n);
            M.reshape(n, m);
            Q.reshape(n, n);
        }
        // RAISING ERROR
        linalg::Matrix S(1, 1);
        S.reshape(2, 2);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "   WORKED" << std::endl;
    }
    test_report("reshape_test");
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

void linalg_tests::arithmetics_test() {
    try {
        for (size_t i = 0; i < TESTS_NO; ++i)
        {
            size_t n = rand_size(1, 10);
            linalg::Matrix A = rand_matrix(n, n), B = rand_matrix(n, n);

            std::cout << (A + A == 2 * A);
            std::cout << (A + A == A * 2);
            std::cout << (A - A == linalg::zeros_matrix(n, n));
            std::cout << (A + (- A) == linalg::zeros_matrix(n, n));
            std::cout << (A * A == linalg::power(A, 2));

            linalg::Matrix C;

            C = A + B;
            std::cout << (C == (A += B));

            std::cout << (A == (A -= B));

            C = A * B;
            std::cout << (C == (A *= B));

            std::cout << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("arithmetics_test");
}

void linalg_tests::linear_algebra_test() {
    try {
        for (size_t i = 0; i < TESTS_NO; ++i)
        {
            size_t n = rand_size(2, 10);
            linalg::Matrix A = rand_matrix(n, n), B = rand_matrix(n, n);

            std::cout << (A * linalg::invert(A) == linalg::identity_matrix(n));
            std::cout << (A * linalg::identity_matrix(n) == A);
            std::cout << (linalg::power(linalg::invert(A), 3) == linalg::power(A, -3));

            std::cout << (linalg::transpose(A + B) == (linalg::transpose(A) + linalg::transpose(B)));
            std::cout << (linalg::transpose(A * B) == (linalg::transpose(B) * linalg::transpose(A)));
            std::cout << (linalg::invert(A * B) == (linalg::invert(B) * linalg::invert(A)));

            std::cout << (std::fabs(linalg::invert(A).det() - (1 / A.det())) < ACCURACY);
            std::cout << (std::fabs(A.norm() - std::sqrt((linalg::transpose(A) * A).trace())) < ACCURACY);

            std::cout << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("linear_algebra_test");
}

void linalg_tests::gauss_test() {
    try {
        for (size_t i = 0; i < 3; ++i)
        {
            size_t n = rand_size(2, 8);
            linalg::Matrix mat = rand_matrix(n, n, true);

            std::cout << mat << "--- turns into ---\n" << linalg::gaussian_elimination(mat) << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    test_report("gauss_test");
}