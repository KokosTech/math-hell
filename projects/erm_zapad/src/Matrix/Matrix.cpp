#include "Matrix.hpp"

#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->data = new double *[rows];

    for (int i = 0; i < rows; i++) {
        this->data[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            this->data[i][j] = 0;
        }
    }
}

Matrix::Matrix(int rows, int cols, double **data) {
    this->rows = rows;
    this->cols = cols;
    this->data = new double *[rows];

    for (int i = 0; i < rows; i++) {
        this->data[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            this->data[i][j] = data[i][j];
        }
    }
}

Matrix::Matrix(const Matrix &m) {
    this->rows = m.rows;
    this->cols = m.cols;
    this->data = new double *[rows];

    for (int i = 0; i < rows; i++) {
        this->data[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            this->data[i][j] = m.data[i][j];
        }
    }
}

int Matrix::getRows() const { return this->rows; }

int Matrix::getCols() const { return this->cols; }

double **Matrix::getData() const { return this->data; }

void Matrix::setData(double **data) { this->data = data; }

double Matrix::get(int row, int col) const { return this->data[row][col]; }

void Matrix::print() const {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            std::cout << this->data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::transpose() const {
    Matrix m(this->cols, this->rows);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            m.data[j][i] = this->data[i][j];
        }
    }

    return m;
}

Matrix Matrix::inverse() const {
    if (this->rows != this->cols) {
        throw std::invalid_argument("Matrix must be square");
    }

    Matrix m(this->rows, this->cols * 2);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            m.data[i][j] = this->data[i][j];
        }
    }

    for (int i = 0; i < this->rows; i++) {
        for (int j = this->cols; j < this->cols * 2; j++) {
            if (i == j - this->cols) {
                m.data[i][j] = 1;
            } else {
                m.data[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < this->rows; i++) {
        double pivot = m.data[i][i];

        for (int j = 0; j < this->cols * 2; j++) {
            m.data[i][j] /= pivot;
        }

        for (int j = 0; j < this->rows; j++) {
            if (i != j) {
                double factor = m.data[j][i];

                for (int k = 0; k < this->cols * 2; k++) {
                    m.data[j][k] -= factor * m.data[i][k];
                }
            }
        }
    }

    Matrix inverse(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = this->cols; j < this->cols * 2; j++) {
            inverse.data[i][j - this->cols] = m.data[i][j];
        }
    }

    return inverse;
}

double Matrix::determinant() const {
    if (this->rows != this->cols) {
        throw std::invalid_argument("Matrix must be square");
    }

    Matrix m(*this);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->rows; j++) {
            if (i != j) {
                double factor = m.data[j][i] / m.data[i][i];

                for (int k = 0; k < this->cols; k++) {
                    m.data[j][k] -= factor * m.data[i][k];
                }
            }
        }
    }

    double det = 1;

    for (int i = 0; i < this->rows; i++) {
        det *= m.data[i][i];
    }

    return det;
}

double *gaussJordanElimination(const Matrix &m) {
    if (m.rows != m.cols - 1) {
        throw std::invalid_argument(
            "Matrix must have one more column than rows");
    }

    for (int i = 0; i < m.rows; i++) {
        double pivot = m.data[i][i];

        for (int j = 0; j < m.cols; j++) {
            m.data[i][j] /= pivot;
        }

        for (int j = 0; j < m.rows; j++) {
            if (i != j) {
                double factor = m.data[j][i];

                for (int k = 0; k < m.cols; k++) {
                    m.data[j][k] -= factor * m.data[i][k];
                }
            }
        }
    }

    double *solution = new double[m.rows];

    for (int i = 0; i < m.rows; i++) {
        solution[i] = m.data[i][m.cols - 1];
    }

    return solution;
}

Matrix Matrix::operator+(const Matrix &m) const {
    if (this->rows != m.rows || this->cols != m.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions");
    }

    Matrix sum(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            sum.data[i][j] = this->data[i][j] + m.data[i][j];
        }
    }

    return sum;
}

Matrix Matrix::operator-(const Matrix &m) const {
    if (this->rows != m.rows || this->cols != m.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions");
    }

    Matrix difference(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            difference.data[i][j] = this->data[i][j] - m.data[i][j];
        }
    }

    return difference;
}

Matrix Matrix::operator*(const Matrix &m) const {
    if (this->cols != m.rows) {
        throw std::invalid_argument("Matrices must have compatible dimensions");
    }

    Matrix product(this->rows, m.cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            for (int k = 0; k < this->cols; k++) {
                product.data[i][j] += this->data[i][k] * m.data[k][j];
            }
        }
    }

    return product;
}

Matrix Matrix::operator*(double const &d) const {
    Matrix product(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            product.data[i][j] = this->data[i][j] * d;
        }
    }

    return product;
}

Matrix Matrix::operator/(double const &d) const {
    Matrix quotient(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            quotient.data[i][j] = this->data[i][j] / d;
        }
    }

    return quotient;
}

Matrix Matrix::operator=(const Matrix &m) {
    if (this != &m) {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->data[i];
        }

        this->rows = m.rows;
        this->cols = m.cols;

        this->data = new double *[this->rows];

        for (int i = 0; i < this->rows; i++) {
            this->data[i] = new double[this->cols];
        }

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                this->data[i][j] = m.data[i][j];
            }
        }
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << m.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            is >> m.data[i][j];
        }
    }
    return is;
}

Matrix::~Matrix() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;
}

