#pragma once

#include <istream>
#include <ostream>

class Matrix {
    private: 
        int rows;
        int cols;
        double **data;
    public:
        Matrix(int rows, int cols);
        Matrix(int rows, int cols, double **data);
        Matrix(const Matrix &m);

        int getRows() const;
        int getCols() const;

        double **getData() const;
        void setData(double **data);

        double get(int row, int col) const;
        void set(int row, int col, double value);

        void print() const;

        Matrix transpose() const;
        Matrix inverse() const;
        double determinant() const;

        friend double *gaussJordanElimination(const Matrix &m);

        Matrix operator+(const Matrix &m) const;
        Matrix operator-(const Matrix &m) const;
        Matrix operator*(const Matrix &m) const;
        Matrix operator/(const Matrix &m) const;
        Matrix operator*(const double &d) const;
        Matrix operator/(const double &d) const;
        Matrix operator=(const Matrix &m);

        friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
        friend std::istream &operator>>(std::istream &in, Matrix &m);

        ~Matrix();
};