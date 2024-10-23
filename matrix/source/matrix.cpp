#include <matrix.h>
#include <stdexcept>
#include <utility>
#include <iomanip>
#include <sstream>
#include <cmath>

#define ACCURACY std::pow(10, -8)


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// --- class Row methods and functions ---
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

double& linalg::Matrix::Row::operator[](size_t col_i) {
    if (col_i >= m_size) {
        throw std::runtime_error("Index is out of range");
    }
    return m_ptr[col_i];
}
const double& linalg::Matrix::Row::operator[](size_t col_i) const {
    if (col_i >= m_size) {
        throw std::runtime_error("Index is out of range");
    }
    return m_ptr[col_i];
}


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// --- class Matrix methods and functions ---
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// constructor with 2 parameters
linalg::Matrix::Matrix(size_t rows, size_t columns) {
    if (rows == 0 || columns == 0) {
        throw std::runtime_error("Shape parameters must be non-zero");
    }
	m_ptr = new double[rows * columns];
	m_rows = rows;
	m_columns = columns;
}

// constructor with 1 parameter
linalg::Matrix::Matrix(size_t rows) {
    if (rows == 0) {
        throw std::runtime_error("Shape parameters must be non-zero");
    }
    m_ptr = new double[rows];
    m_rows = rows;
    m_columns = 1;
}

// copy constructor
linalg::Matrix::Matrix(const Matrix& mat) {
    if (mat.empty()) {
        m_ptr = nullptr;
        m_rows = 0;
        m_columns = 0;
    }
    else {
        m_ptr = new double[mat.size()];
        m_rows = mat.rows();
        m_columns = mat.columns();
        for (size_t i = 0; i < mat.size(); ++i) {
            m_ptr[i] = mat.m_ptr[i];
        }
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
    if (lst.size() == 0) {
        m_rows = 0;
        m_columns = 0;
        m_ptr = nullptr;
    }
    else {
        size_t i = 0;
        m_rows = lst.size();
        m_columns = 1;
        m_ptr = new double[lst.size()];
        for (auto el: lst) {
            m_ptr[i++] = static_cast<double>(el);
        }
    }
}

// 2-d init list constructor
linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst) {
    size_t cols = lst.begin()->size();
    for (std::initializer_list<double> small_lst: lst) {
        if (small_lst.size() != cols) {
            throw std::runtime_error("Different sizes of rows in inner list");
        }
    }
    if (cols== 0) {
        m_rows = 0;
        m_columns = 0;
        m_ptr = nullptr;
    }
    else {
        size_t i = 0;
        m_rows = lst.size();
        m_columns = cols;
        m_ptr = new double[m_rows * m_columns];
        for (std::initializer_list<double> small_lst: lst) {
            for (double el: small_lst) {
                m_ptr[i++] = el;
            }
        }
    }
}

// copy operator =
linalg::Matrix& linalg::Matrix::operator=(const Matrix& mat) {
    if (mat.empty()) {
        m_ptr = nullptr;
        m_rows = 0;
        m_columns = 0;
        return *this;
    }
    if (mat.rows() != m_rows || mat.columns() != m_columns) {
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

// operators for calling matrix elements
double& linalg::Matrix::operator()(size_t row, size_t col) {
    if (row >= m_rows || col >= m_columns) {
        throw std::runtime_error("Index is out of range");
    }
    return m_ptr[m_columns * row + col];
}
const double& linalg::Matrix::operator()(size_t row, size_t col) const {
    if (row >= m_rows || col >= m_columns) {
        throw std::runtime_error("Index is out of range");
    }
    return m_ptr[m_columns * row + col];
}
linalg::Matrix::Row linalg::Matrix::operator[](size_t row_i) {
    if (row_i >= m_rows) {
        throw std::runtime_error("Index is out of range");
    }
    return {*this, row_i};
}
const linalg::Matrix::Row linalg::Matrix::operator[](size_t row_i) const {
    if (row_i >= m_rows) {
        throw std::runtime_error("Index is out of range");
    }
    return {*this, row_i};
}

// visualising method (operator <<)
std::ostream& linalg::operator<<(std::ostream& left, const Matrix& right) {
    if (right.size() == 0) {
        left << "| |\n";
        return left;
    }
    std::stringstream sout;
    size_t maxlength = 0;
    size_t firstmaxlength = 0;

    for (size_t i = 0; i < right.rows(); ++i) {
        for (size_t j = 0; j < right.columns(); ++j) {
            sout << right(i, j);
            maxlength = std::max(maxlength, sout.str().size());
            if (j == 0) { firstmaxlength = std::max(firstmaxlength, sout.str().size());}
            sout.str("");
        }
    }

    for (size_t i = 0; i < right.rows(); ++i) {
        left << '|';
        left << std::setw(firstmaxlength) << right(i, 0);
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
    if (m_rows == 0 || m_columns == 0) {
        throw std::runtime_error("Matrix has size 0");
    }

    m_rows = rows;
    m_columns = cols;
}

// method for getting rid of elements which are lesser than ACCURACY
void linalg::Matrix::check_zeros() {
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            if (std::fabs((*this)(i, j)) < ACCURACY) {(*this)(i, j) = 0; }
        }
    }
}

// operator +=
linalg::Matrix& linalg::Matrix::operator+=(const Matrix& mat) {
    if (mat.rows() != m_rows || mat.columns() != m_columns) {
        throw std::runtime_error("Matrix shapes are not suitable");
    }
    for (size_t i = 0; i < this->size(); ++i) {
        m_ptr[i] += mat.m_ptr[i];
    }
    return *this;
}

// operator -=
linalg::Matrix& linalg::Matrix::operator-=(const Matrix& mat) {
    if (mat.rows() != m_rows || mat.columns() != m_columns) {
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
    Matrix copy1 = (*this);
    Matrix copy2 = mat;
    for (size_t row = 0; row < m_rows; ++row) {
        for (size_t col = 0; col < m_columns; ++col) {
            (*this)(row, col) = 0;
            for (size_t i = 0; i < m_columns; ++i) {
                (*this)(row, col) += copy1(row, i) * copy2(i, col);
            }
        }
    }
    (*this).check_zeros();
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

// unary minus
linalg::Matrix linalg::Matrix::operator-() {
    Matrix result = (*this);
    result *= (-1);
    return result;
}

// operator == for comparing matrices
bool linalg::operator==(const linalg::Matrix &mat1, const linalg::Matrix &mat2) {
    if (mat1.rows() != mat2.rows() || mat1.columns() != mat2.columns()) {
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
    return !(mat1 == mat2);
}

// operator +
linalg::Matrix linalg::operator+(const linalg::Matrix& mat1, const linalg::Matrix& mat2) {
    Matrix result = mat1;
    result += mat2;
    return result;
}

// operator -
linalg::Matrix linalg::operator-(const linalg::Matrix& mat1, const linalg::Matrix& mat2) {
    Matrix result = mat1;
    result -= mat2;
    return result;
}

// operator * for matrix multiplication
linalg::Matrix linalg::operator*(const linalg::Matrix& mat1, const linalg::Matrix& mat2) {
    Matrix result = mat1;
    result *= mat2;
    return result;
}

// operator * for multiplying matrix by a number (when number on the left)
linalg::Matrix linalg::operator*(const double& value, const linalg::Matrix& mat) {
    Matrix result = mat;
    result *= value;
    return result;
}

// operator * for multiplying matrix by a number (when number on the right)
linalg::Matrix linalg::operator*(const linalg::Matrix& mat, const double& value) {
    Matrix result = mat;
    result *= value;
    return result;
}

// finding trace (sum of elements on main diagonal)
double linalg::Matrix::trace() const {
    if (m_rows == 0 || m_columns == 0) {
        throw std::runtime_error("Matrix has size 0");
    }
    size_t n = m_rows;
    if (m_rows != m_columns) {
        if (m_rows > m_columns) { n = m_columns; }
    }
    double result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += (*this)(i, i);
    }
    return result;
}

// finding Frobenius norm
double linalg::Matrix::norm() const {
    if (m_rows == 0 || m_columns == 0) {
        throw std::runtime_error("Matrix has size 0");
    }
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
    if (m_rows == 0 || m_columns == 0) {
        throw std::runtime_error("Matrix has size 0");
    }
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
    size_t n = mat.rows(), m = mat.columns();
    Matrix copy(m, n);
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            copy(i, j) = mat(j, i);
        }
    }
    return copy;
}

// finding inverse matrix
linalg::Matrix linalg::invert(const linalg::Matrix& mat) {
    double det = mat.det();
    if (std::fabs(det) < ACCURACY) {
        throw std::runtime_error("Matrix determinant is 0; inverse matrix cannot be found");
    }
    // M^(-1) = ( 1/det(M) ) * transpose({Aij})
    // where Aij = (-1)^(i + j) * minor(M, i, j)
    size_t n = mat.rows();
    Matrix result(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            result(i, j) = std::pow(-1, i + j) * minor(mat, i, j);
        }
    }
    result = transpose(result);
    result = (1 / det) * result;
    return result;
}

// generating rows x cols matrix, filled with zeros
linalg::Matrix linalg::zeros_matrix(size_t rows, size_t cols) {
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = 0;
        }
    }
    return result;
}

// generating n x n identity matrix
linalg::Matrix linalg::identity_matrix(size_t n) {
    Matrix result = zeros_matrix(n, n);
    for (size_t i = 0; i < n; ++i) {
        result(i, i) = 1;
    }
    return result;
}

// finding mat^deg
linalg::Matrix linalg::power(const linalg::Matrix& mat, const int& deg) {
    if (mat.rows() != mat.columns()) {
        throw std::runtime_error("Matrix is not square");
    }
    if (deg < 0) {
        return power(invert(mat), -deg);
    }
    else if (deg == 0) {
        return identity_matrix(mat.rows());
    }
    else if (deg % 2 == 0) {
        Matrix tmp = power(mat, deg / 2);
        return tmp * tmp;
    }
    else {
        return power(mat, deg - 1) * mat;
    }
}