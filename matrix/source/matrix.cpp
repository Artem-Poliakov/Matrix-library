#include <matrix.h>
#include <iostream>
#include <stdexcept>

// constructor with 2 parameters
linalg::Matrix::Matrix(size_t rows, size_t columns) {
	m_ptr = new double[rows * columns];
	m_rows = rows;
	m_columns = columns;
}

// constructor with 1 parameter
linalg::Matrix::Matrix(size_t rows) {
    m_ptr = new double[rows];
    m_rows = rows;
    m_columns = 1;
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

// 1-d init list constructor
linalg::Matrix::Matrix(std::initializer_list<double> lst) {
    size_t i = 0;
    m_rows = lst.size();
    m_columns = 1;
    m_ptr = new double[lst.size()];
    for (auto el: lst) {
        m_ptr[i++] = static_cast<double>(el);
    }
}

// 2-d init list constructor
linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst) {
    size_t i = 0;
    m_rows = lst.size();
    m_columns = lst.begin()->size();
    m_ptr = new double[m_rows * m_columns];
    for (std::initializer_list<double> small_lst: lst) {
        for (double el: small_lst) {
            m_ptr[i++] = el;
        }
    }
}

// copy operator=
linalg::Matrix& linalg::Matrix::operator=(const Matrix& mat) {
    if (mat.rows() != m_rows or mat.columns() != m_columns) {
        delete[] m_ptr;
        m_ptr = new double[mat.size()];
        m_rows = mat.rows();
        m_columns = mat.columns();
    }
    for (size_t i = 0; i < this->size(); i++) {
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

// visualising method
void linalg::Matrix::print() {
    for (size_t i = 0; i < m_rows; ++i) {
        std::cout << "| ";
        for (size_t j = 0; j < m_columns; ++j) {
            std::cout << (*this)(i, j) << ' ';
        }
        std::cout << "|\n";
    }
    std::cout << "\n";
}

// method to change matrix shape
void linalg::Matrix::reshape(size_t rows, size_t cols) {
    if (rows * cols != this->size()) {
        throw std::runtime_error("Matrix sizes are not suitable");
    }

    m_rows = rows;
    m_columns = cols;
}
