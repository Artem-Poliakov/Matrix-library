#include <matrix.h>
#include <iostream>

linalg::Matrix::Matrix(size_t rows, size_t columns) {
	m_ptr = new double[rows * columns];
	m_rows = rows;
	m_columns = columns;
}

linalg::Matrix::Matrix(const Matrix& mat) {
    m_ptr = new double[mat.rows() * mat.columns()];
    m_rows = mat.rows();
    m_columns = mat.columns();
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] = mat.m_ptr[i];
    }
}
linalg::Matrix::Matrix(Matrix&& mat) {
    std::swap(m_ptr, mat.m_ptr);
    std::swap(m_rows, mat.m_rows);
    std::swap(m_columns, mat.m_columns);
}