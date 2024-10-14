#pragma once
#include <cstddef>

namespace linalg {
    class Matrix {
    public:

        // constructors & destructor
        Matrix() {}
        Matrix(size_t rows, size_t columns);
        Matrix(const Matrix& mat);
        Matrix(Matrix&& mat);
        ~Matrix() { delete[] m_ptr; }

        // operators
        Matrix& operator=(const Matrix& mat);
        Matrix& operator=(Matrix&& mat);

        // shape methods
        size_t rows() const { return m_rows; }
        size_t columns() const { return m_columns; }
        size_t size() const { return m_rows * m_columns; }
        bool empty() const { return m_ptr == nullptr; }

    private:
        double *m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
    };
}