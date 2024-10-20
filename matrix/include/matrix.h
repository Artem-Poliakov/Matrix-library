#pragma once
#include <cstddef>
#include <initializer_list>
#include <ostream>

namespace linalg {
    class Matrix {
    public:
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
        double& operator()(size_t row, size_t col) const { return m_ptr[m_columns * row + col]; }
        Matrix& operator+=(const Matrix& mat);
        Matrix& operator-=(const Matrix& mat);
        Matrix& operator*=(const Matrix& mat);
        Matrix& operator*=(const double& value);

        // shape methods
        size_t rows() const { return m_rows; }
        size_t columns() const { return m_columns; }
        size_t size() const { return m_rows * m_columns; }
        bool empty() const { return m_ptr == nullptr; }
        void reshape(size_t rows, size_t cols);

        // linear algebra methods
        double trace() const;
        double norm() const;
        double det() const;

        // other methods
        void check_zeros() const;

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
    Matrix inverse(const Matrix& mat);
}