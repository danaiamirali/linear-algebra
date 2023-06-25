#include "Matrix.hpp"

Matrix Matrix::operator*(const Matrix &other) const {

    if (this->n != other.m) {
        throw MULTIPLY_ERROR();
    }

    Matrix newMatrix = Matrix(this->m, other.n);

    for (int i = 0; i < newMatrix.m; i++) {
        for (int j = 0; j < newMatrix.n; j++) {
            Fraction sum = 0;
            for (int k = 0; k < this->n; k++) {
                sum += this->matrix[i][k] * other.matrix[k][j];
            }
            newMatrix.matrix[i][j] = sum;
        }
    }

    return newMatrix;
}

Matrix Matrix::operator*(const int c) const {

    Matrix newMatrix = Matrix(this->m, this->n);

    for (int i = 0; i < newMatrix.m; i++) {
        for (int j = 0; j < newMatrix.n; j++) {
                newMatrix.matrix[i][j] = this->matrix[i][j] * c;
        }
    }

    return newMatrix;
}

