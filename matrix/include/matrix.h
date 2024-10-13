#pragma once
#include <cstddef>

namespace linalg {
    class Matrix {
    public:
        Matrix() {}
        Matrix(size_t rows, size_t columns);
        Matrix(const Matrix& mat);
        Matrix(Matrix&& mat);
        ~Matrix() { delete[] m_ptr; }

        Matrix& operator=(const Matrix& mat);
        Matrix& operator=(Matrix&& mat);

        size_t rows() const { return m_rows; }
        size_t columns() const { return m_columns; }
        size_t size() const { return m_rows * m_columns; }

    private:
        double *m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
    };
}