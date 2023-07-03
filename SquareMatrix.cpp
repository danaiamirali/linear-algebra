#include "SquareMatrix.hpp"
#include "IdentityMatrix.hpp"

Fraction SquareMatrix::determinant() {
    /*
    TO-DO
    */

   return 0;
}

SquareMatrix SquareMatrix::inverse() {
    // Row reduce the augmented matrix [A | I]
    // If A is roq equivalent to I, then [A | I] will be row equivalent to [I | A^-1]
    // Otherwise, A is not invertible
    Matrix aug = this->concat(IdentityMatrix(this->n)).rref();

    // Check if A is invertible
    for (int i = 0; i < aug.m; i++) {
        bool isOne = (aug.matrix[i][i] == 1);
        bool isZeros = true;
        for (int j = 0; j < aug.m; j++) {
            if (j != i && aug.matrix[i][j] != 0) {
                isZeros = false;
                break;
            }
        }

        if (!isOne || !isZeros) {
            throw NOT_INVERTIBLE();
        }
    }

    // Extract A^-1 from [I | A^-1]
    Matrix inv = aug.submatrix(0, this->n + 1, aug.m, aug.n);

    return SquareMatrix(inv);
}