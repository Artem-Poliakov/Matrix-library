#include <matrix.h>
#include <stdexcept>
#include <utility>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <iostream>

#define ACCURACY std::pow(10, -8)

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

// copy operator =
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

// move operator =
linalg::Matrix& linalg::Matrix::operator=(Matrix&& mat) {
    std::swap(m_ptr, mat.m_ptr);
    std::swap(m_rows, mat.m_rows);
    std::swap(m_columns, mat.m_columns);
    return *this;
}

// visualising method (operator <<)
std::ostream& linalg::operator<<(std::ostream& left, const Matrix& right) {
    if (right.size() == 0) {
        left << "| |";
        return left;
    }
    std::stringstream sout;
    size_t maxlength = 0;
    for (size_t i = 0; i < right.rows(); ++i) {
        for (size_t j = 0; j < right.columns(); ++j) {
            sout << right(i, j);
            maxlength = std::max(maxlength, sout.str().size());
            sout.str("");
        }
    }

    for (size_t i = 0; i < right.rows(); ++i) {
        left << '|';
        left << std::setw(maxlength) << right(i, 0);
        for (size_t j = 1; j < right.columns(); ++j) {
            left << std::setw(maxlength + 1) << right(i, j);
        }
        left << '|' << '\n';
    }
    return left;
}

// method to change matrix shape
void linalg::Matrix::reshape(size_t rows, size_t cols) {
    if (rows * cols != this->size()) {
        throw std::runtime_error("Matrix sizes are not suitable");
    }

    m_rows = rows;
    m_columns = cols;
}

// operator +=
linalg::Matrix& linalg::Matrix::operator+=(const Matrix& mat) {
    if (mat.rows() != m_rows or mat.columns() != m_columns) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    for (size_t i = 0; i < this->size(); ++i) {
        m_ptr[i] += mat.m_ptr[i];
    }
    return *this;
}

// operator -=
linalg::Matrix& linalg::Matrix::operator-=(const Matrix& mat) {
    if (mat.rows() != m_rows or mat.columns() != m_columns) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    for (size_t i = 0; i < this->size(); ++i) {
        m_ptr[i] -= mat.m_ptr[i];
    }
    return *this;
}

// operator *= for matrix multiplication
linalg::Matrix& linalg::Matrix::operator*=(const Matrix& mat) {
    if (m_columns != mat.rows()) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    Matrix copy = (*this);
    m_rows = copy.rows(), m_columns = mat.columns();
    for (size_t row = 0; row < copy.rows(); ++row) {
        for (size_t col = 0; col < mat.columns(); ++col) {
            for (size_t i = 0; i < copy.columns(); ++i) {
                (*this)(row, col) += (copy(row, i) * mat(i, col));
            }
        }
    }
    return *this;
}

// operator *= for multiplying matrix by a number
linalg::Matrix& linalg::Matrix::operator*=(const double& value) {
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            (*this)(i, j) *= value;
        }
    }
    return *this;
}

// operator == for comparing matrices
bool linalg::operator==(const linalg::Matrix &mat1, const linalg::Matrix &mat2) {
    if (mat1.rows() != mat2.rows() or mat1.columns() != mat2.columns()) {
        return false;
    }
    for (size_t i = 0; i < mat1.rows(); ++i) {
        for (size_t j = 0; j < mat1.columns(); ++j) {
            if (std::abs(mat1(i, j) - mat2(i, j)) > ACCURACY) {
                return false;
            }
        }
    }
    return true;
}

// operator != for comparing matrices
bool linalg::operator!=(const linalg::Matrix &mat1, const linalg::Matrix &mat2) {
    return not(mat1 == mat2);
}

// operator +
linalg::Matrix linalg::operator+(const linalg::Matrix& mat1, const linalg::Matrix& mat2) {
    if (mat1.rows() != mat2.rows() or mat1.columns() != mat2.columns()) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    Matrix result = Matrix(mat1.rows(), mat1.columns());
    for (size_t i = 0; i < mat1.rows(); ++i) {
        for (size_t j = 0; j < mat1.columns(); ++j) {
            result(i, j) = mat1(i, j) + mat2(i, j);
        }
    }
    return result;
}

// operator -
linalg::Matrix linalg::operator-(const linalg::Matrix& mat1, const linalg::Matrix& mat2) {
    if (mat1.rows() != mat2.rows() or mat1.columns() != mat2.columns()) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    Matrix result = Matrix(mat1.rows(), mat1.columns());
    for (size_t i = 0; i < mat1.rows(); ++i) {
        for (size_t j = 0; j < mat1.columns(); ++j) {
            result(i, j) = mat1(i, j) - mat2(i, j);
        }
    }
    return result;
}

// operator * for matrix multiplication
linalg::Matrix linalg::operator*(const linalg::Matrix& mat1, const linalg::Matrix& mat2) {
    if (mat1.columns() != mat2.rows()) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    Matrix result = Matrix(mat1.rows(), mat2.columns());
    for (size_t row = 0; row < mat1.rows(); ++row) {
        for (size_t col = 0; col < mat2.columns(); ++col) {
            for (size_t i = 0; i < mat1.columns(); ++i) {
                result(row, col) += mat1(row, i) * mat2(i, col);
            }
        }
    }
    return result;
}

// operator * for multiplying matrix by a number (when number on the left)
linalg::Matrix linalg::operator*(const double& value, const linalg::Matrix& mat) {
    Matrix result(mat.rows(), mat.columns());
    for (size_t i = 0; i < mat.rows(); ++i) {
        for (size_t j = 0; j < mat.columns(); ++j) {
            result(i, j) = mat(i, j) * value;
        }
    }
    return result;
}

// operator * for multiplying matrix by a number (when number on the right)
linalg::Matrix linalg::operator*(const linalg::Matrix& mat, const double& value) {
    return value * mat;
}

// finding trace (sum of elements on main diagonal)
double linalg::Matrix::trace() const {
    if (m_rows != m_columns) {
        throw std::runtime_error("Matrix is not square");
    }
    double result = 0;
    for (size_t i = 0; i < m_rows; ++i) {
        result += (*this)(i, i);
    }
    return result;
}

// finding Frobenius norm
double linalg::Matrix::norm() const {
    double result = 0;
    for (size_t i = 0; i < this->size(); ++i) {
        result += std::pow(m_ptr[i], 2);
    }
    return std::sqrt(result);
}

// matrix echelon reduction
linalg::Matrix linalg::gaussian_elimination(const linalg::Matrix& mat) {
    size_t n = mat.rows();
    size_t m = mat.columns();
    // will work with copy of the matrix
    Matrix copy = mat;
    // will count all row swaps and at the end change the sign of one row depending on it's oddness
    size_t swap_counter = 0;

    for (size_t i = 0; i < n; ++i) {
        // finding maximum element in a column
        double max_el = std::fabs(copy(i, i));
        size_t max_row = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (std::fabs(copy(k, i)) > max_el) {
                max_el = std::fabs(copy(k, i));
                max_row = k;
            }
        }
        // swapping current row with the one, where maximum element was found
        if (i != max_row) {
            for (size_t k = i; k < m; ++k) {
                std::swap(copy(max_row, k), copy(i, k));
            }
            ++swap_counter;
        }
        // gaussian method
        for (size_t k = i + 1; k < n; ++k) {
            // if there is no more non-zero rows: end the algorithm
            if (std::fabs(copy(i, i)) < ACCURACY) {
                return copy;
            }
            // else: continue
            double coefficient = copy(k, i) / copy(i, i);
            for (size_t j = i; j < m; ++j) {
                copy(k, j) -= coefficient * copy(i, j);
                if (std::fabs(copy(k, j)) < ACCURACY) {
                    copy(k, j) = 0;
                }
            }
        }
    }
    // changing sign of one row if swap counter is odd
    if (swap_counter % 2 != 0) {
        for (size_t p = 0; p < m; ++p) {
            copy(0, p) *= (-1);
        }
    }

    return copy;
}

// finding determinant
double linalg::Matrix::det() const {
    if (m_rows != m_columns) {
        throw std::runtime_error("Matrix is not square");
    }
    double det = 1;
    Matrix processed_mat = gaussian_elimination(*this);
    for (size_t i = 0; i < m_rows; ++i) {
        det *= processed_mat(i, i);
    }
    return det;
}

// finding minor of a matrix
double linalg::minor(const linalg::Matrix& mat, size_t row, size_t col) {
    if (mat.rows() != mat.columns()) {
        throw std::runtime_error("Matrix is not square");
    }
    // making a copy of mat, but w/o one row and one column
    Matrix processed_mat(mat.rows() - 1, mat.columns() - 1);
    int flag_i = 0;
    for (size_t i = 0; i < mat.rows(); ++i) {
        int flag_j = 0;
        if (i == row) { ++flag_i; }
        else {
            for (size_t j = 0; j < mat.columns(); ++j) {
                if (j == col) { ++flag_j; }
                else { processed_mat(i - flag_i, j - flag_j) = mat(i, j); }
            }
        }
    }
    // finding its determinant
    return processed_mat.det();
}

// expanding one matrix horizontally, using another (returns a copy of result)
linalg::Matrix linalg::concatenate(const Matrix& mat1, const Matrix& mat2) {
    size_t n = mat1.rows();
    if (n != mat2.rows()) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    Matrix extended_mat(n, mat1.columns() + mat2.columns());
    for (size_t i = 0; i < n; ++i) {
        // full the first part of a row (elements of mat1)
        for (size_t j1 = 0; j1 < mat1.columns(); ++j1) {
            extended_mat(i, j1) = mat1(i, j1);
        }
        // full the second part of a row (elements of mat2)
        for (size_t j2 = 0; j2 < mat2.columns(); ++j2) {
            extended_mat(i, mat1.columns() + j2) = mat2(i, j2);
        }
    }
    return extended_mat;
}

// transposing matrix
linalg::Matrix linalg::transpose(const linalg::Matrix& mat) {
    size_t n = mat.rows();
    if (n != mat.columns()) {
        throw std::runtime_error("Matrix is not square");
    }
    Matrix copy(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            copy(i, j) = mat(j, i);
        }
    }
    return copy;
}