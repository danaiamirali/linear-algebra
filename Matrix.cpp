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

Matrix Matrix::rref() {
    Matrix newMatrix (*this);

    refHelper(newMatrix, 0, 0);

    return newMatrix;
}

Matrix Matrix::ref() {
    Matrix newMatrix (*this);

    refHelper(newMatrix, 0, 0);

    return newMatrix;
}

// Function to perform row reduction
void Matrix::refHelper(Matrix& mat, int currentRow, int currentCol) {
    int rows = mat.m;
    int cols = mat.n;

    // Base case: if we reach the last row or last column, return
    if (currentRow == rows || currentCol == cols) {
        return;
    }

    // Find the non-zero entry in the current column
    int nonZeroRow = currentRow;
    while (nonZeroRow < rows && mat[nonZeroRow][currentCol] == 0) {
        nonZeroRow++;
    }

    if (nonZeroRow == rows) {
        // If all entries in the current column are zero, move to the next column
        refHelper(mat, currentRow, currentCol + 1);
    } else {
        // Swap the current row with the row containing the non-zero entry
        mat.swapRows(currentRow, nonZeroRow);

        
        // Scale the current row to make the leading entry 1
        Fraction scale = mat[currentRow][currentCol];
        for (int j = currentCol; j < cols; j++) {
            mat[currentRow][j] /= scale;
        }
        

        // Perform row operations to make all other entries in the current column zero
        for (int i = 0; i < rows; i++) {
            if (i != currentRow) {
                Fraction factor = mat[i][currentCol];
                for (int j = currentCol; j < cols; j++) {
                    mat[i][j] -= factor * mat[currentRow][j];
                }
            }
        }

        // Recursive call for the next row and next column
        refHelper(mat, currentRow + 1, currentCol + 1);
    }
}
