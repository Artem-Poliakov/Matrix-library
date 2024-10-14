#pragma once
#include <cstddef>
#include <initializer_list>

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
        double& operator()(size_t row, size_t column) { return m_ptr[m_columns * row + column]; }

        // shape methods
        size_t rows() const { return m_rows; }
        size_t columns() const { return m_columns; }
        size_t size() const { return m_rows * m_columns; }
        bool empty() const { return m_ptr == nullptr; }

        // visualising method
        void print();

    private:
        double *m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
    };
}