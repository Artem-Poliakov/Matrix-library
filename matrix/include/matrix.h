#pragma once
#include <cstddef>
#include <initializer_list>
#include <ostream>

namespace linalg {
    class Matrix {
    public:
        // proxy class ( just for getting matrix elements by calling "matrix[][]")
        class Row {
            friend Matrix;
        public:
            double& operator[](size_t col_i);
            const double& operator[](size_t col_i) const;
        private:
            Row(Matrix& mat, size_t row_i) :m_size(mat.m_columns) { m_ptr = mat.m_ptr + row_i * mat.m_columns; }
            Row(const Matrix& mat, size_t row_i) :m_size(mat.m_columns) { m_ptr = mat.m_ptr + row_i * mat.m_columns; }

            double* m_ptr = nullptr;
            size_t m_size = 0;
        };

        // constructors & destructor
        Matrix() {}
        Matrix(size_t rows, size_t columns);
        Matrix(size_t rows);
        Matrix(const Matrix& mat);
        Matrix(Matrix&& mat);
        Matrix(std::initializer_list<double> lst);
        Matrix(std::initializer_list<std::initializer_list<double>> lst);
        ~Matrix() { delete[] m_ptr; }

        // operators
        Matrix& operator=(const Matrix& mat);
        Matrix& operator=(Matrix&& mat);
        double& operator()(size_t row, size_t col);
        const double& operator()(size_t row, size_t col) const;
        Row operator[](size_t row_i);
        const Row operator[](size_t row_i) const;

        Matrix& operator+=(const Matrix& mat);
        Matrix& operator-=(const Matrix& mat);
        Matrix& operator*=(const Matrix& mat);
        Matrix& operator*=(const double& value);
        Matrix operator-();

        // shape methods
        size_t rows() const noexcept { return m_rows; }
        size_t columns() const noexcept { return m_columns; }
        size_t size() const noexcept { return m_rows * m_columns; }
        bool empty() const noexcept { return m_ptr == nullptr; }
        void reshape(size_t rows, size_t cols);

        // linear algebra methods
        double trace() const;
        double norm() const;
        double det() const;

        // other methods
        void check_zeros();

    private:
        double *m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
    };

    // arithmetic operators
    Matrix operator+(const Matrix& mat1, const Matrix& mat2);
    Matrix operator-(const Matrix& mat1, const Matrix& mat2);
    Matrix operator*(const Matrix& mat1, const Matrix& mat2);
    Matrix operator*(const Matrix& mat, const double& value);
    Matrix operator*(const double& value, const Matrix& mat);

    // logic operators
    bool operator==(const Matrix& mat1, const Matrix& mat2);
    bool operator!=(const Matrix& mat1, const Matrix& mat2);

    // visualizing operator
    std::ostream& operator<<(std::ostream& left, const Matrix& right);

    // linear algebra functions
    Matrix gaussian_elimination(const Matrix& mat);
    double minor(const Matrix& mat, size_t row, size_t col);
    Matrix concatenate(const Matrix& mat1, const Matrix& mat2);
    Matrix transpose(const Matrix& mat);
    Matrix invert(const Matrix& mat);
    Matrix power(const Matrix& mat, const int& deg);

    // certain types of matrices
    Matrix identity_matrix(size_t n);
    Matrix zeros_matrix(size_t rows, size_t cols);
}