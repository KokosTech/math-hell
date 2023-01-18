#include "Matrix.hpp"

#include <iomanip>
#include <iostream>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->data = nullptr;
}

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->data = new double *[rows];

    for (int i = 0; i < rows; i++) {
        this->data[i] = new double[cols];
        for (int j = 0; j < cols; j++) this->data[i][j] = 0;
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

double Matrix::get(int row, int col) const {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols)
        throw std::out_of_range("Error: Index out of range");

    return this->data[row][col];
}

void Matrix::set(int row, int col, double value) {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols)
        throw std::out_of_range("Error: Index out of range");

    this->data[row][col] = value;
}

void Matrix::print() const {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) printf("%.4f\t", this->data[i][j]);
        std::cout << std::endl;
    }
}

double *gaussJordanElimination(const Matrix &m) {
    if (m.rows != m.cols - 1)
        throw std::invalid_argument(
            "Matrix must have one more column than rows");

    for (int i = 0; i < m.rows; i++) {
        double pivot = m.data[i][i];

        for (int j = 0; j < m.cols; j++) {
            if (pivot == 0)
                throw std::invalid_argument(
                    "Matrix is singular (no unique solution)");

            m.data[i][j] /= pivot;
        }

        for (int j = 0; j < m.rows; j++) {
            if (i != j) {
                double factor = m.data[j][i];

                for (int k = 0; k < m.cols; k++)
                    m.data[j][k] -= factor * m.data[i][k];
            }
        }
    }

    double *solution = new double[m.rows];
    for (int i = 0; i < m.rows; i++) solution[i] = m.data[i][m.cols - 1];

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
            os << std::fixed << std::setprecision(4) << m.data[i][j] << "\t";
        }
        os << '\n';
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
    if (this->data == nullptr) return;

    for (int i = 0; i < this->rows; i++) delete[] this->data[i];
    delete[] this->data;
}