#include <matrix.h>
#include <iostream>

// constructor with parameters
linalg::Matrix::Matrix(size_t rows, size_t columns) {
	m_ptr = new double[rows * columns];
	m_rows = rows;
	m_columns = columns;
}

// copy constructor
linalg::Matrix::Matrix(const Matrix& mat) {
    m_ptr = new double[mat.size()];
    m_rows = mat.rows();
    m_columns = mat.columns();
    for (size_t i = 0; i < mat.size(); ++i) {
        m_ptr[i] = mat.m_ptr[i];
    }
}

// move constructor
linalg::Matrix::Matrix(Matrix&& mat) {
    std::swap(m_ptr, mat.m_ptr);
    std::swap(m_rows, mat.m_rows);
    std::swap(m_columns, mat.m_columns);
}

// copy operator=
linalg::Matrix& linalg::Matrix::operator=(const Matrix& mat) {
    if (mat.rows() != m_rows or mat.columns() != m_columns) {
        delete[] m_ptr;
        m_ptr = new double[mat.size()];
        m_rows = mat.rows();
        m_columns = mat.columns();
    }
    for (size_t i = 0; i < this->size(); ++i) {
        m_ptr[i] = mat.m_ptr[i];
    }
    return *this;
}

// move operator=
linalg::Matrix& linalg::Matrix::operator=(Matrix&& mat) {
    std::swap(m_ptr, mat.m_ptr);
    std::swap(m_rows, mat.m_rows);
    std::swap(m_columns, mat.m_columns);
    return *this;
}