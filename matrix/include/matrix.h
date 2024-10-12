#pragma once
#include <cstddef>

class Matrix {
public:
    Matrix() { }
    Matrix(size_t rows, size_t columns);
    ~Matrix() { delete[] m_ptr; }

    size_t rows() const { return m_rows; }
    size_t columns() const { return m_columns; }
private:
    double* m_ptr = nullptr;
    size_t m_rows = 0;
    size_t m_columns = 0;
};
