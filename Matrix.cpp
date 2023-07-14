#include "Matrix.hpp"

/*
 *
 * MATRIX MULTIPLICATION
 *
*/


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


/*
 *
 * ROW ECHELON FORMS
 *
*/

Matrix Matrix::rref() {
    Matrix newMatrix (*this);

    reducer(newMatrix, 0, 0, true, false);

    return newMatrix;
}

Matrix Matrix::rref(bool verbose) {
    Matrix newMatrix (*this);

    reducer(newMatrix, 0, 0, true, verbose);

    return newMatrix;
}

Matrix Matrix::ref() {
    Matrix newMatrix (*this);

    reducer(newMatrix, 0, 0, false, false);

    return newMatrix;
}

Matrix Matrix::ref(bool verbose) {
    Matrix newMatrix (*this);

    reducer(newMatrix, 0, 0, false, verbose);

    return newMatrix;
}

// Function to perform row reduction
void Matrix::reducer(Matrix& mat, int currentRow, int currentCol, bool rref, bool verbose) {
    int rows = mat.m;
    int cols = mat.n;

    // Base case: if we reach the last row or last column, return
    if (currentRow == rows || currentCol == cols ) {
        return;
    }

    // Find the non-zero entry in the current column
    int nonZeroRow = currentRow;
    while (nonZeroRow < rows && mat[nonZeroRow][currentCol] == 0) {
        nonZeroRow++;
    }

    if (nonZeroRow == rows) {
        // If all entries in the current column are zero, move to the next column
        reducer(mat, currentRow, currentCol + 1, rref, verbose);
    } else {
        // Swap the current row with the row containing the non-zero entry
        mat.swapRows(currentRow, nonZeroRow);

        // Scale the current row to make the leading entry 1
        if (rref) {
            
            Fraction scale = mat[currentRow][currentCol];

            if (verbose) {
                cout << "Row " << currentRow + 1 << " scaled by " << scale << endl;
            }

            for (int j = currentCol; j < cols; j++) {
                try {
                    mat[currentRow][j] /= scale;
                }
                catch (ZERO_DENOMINATOR) {
                    continue;
                }
            }

            if (verbose) {
                cout << mat << endl;
            }
        }        

        // Perform row operations to make all other entries in the current column zero
        if (rref) {
            for (int i = 0; i < rows; i++) {
                if (i != currentRow) {
                    Fraction factor = mat[i][currentCol] / mat[currentRow][currentCol];

                    if (verbose) {
                        cout << "Row " << i + 1 << " = Row " << i + 1 << " - " << factor << " * Row " << currentRow + 1 << endl;
                    }
                    
                    for (int j = currentCol; j < cols; j++) {
                        mat[i][j] -= factor * mat[currentRow][j];
                    }

                    if (verbose) {
                    cout << mat << endl;
                    }
                }
            }
        }
        else {
            for (int i = currentRow + 1; i < rows; i++) {
                Fraction factor = mat[i][currentCol] / mat[currentRow][currentCol];

                if (verbose) {
                    cout << "Row " << i + 1 << " = Row " << i + 1 << " - " << factor << " * Row " << currentRow + 1 << endl;
                }
                
                for (int j = currentCol; j < cols; j++) {
                    mat[i][j] -= factor * mat[currentRow][j];
                }

                if (verbose) {
                cout << mat << endl;
                }
            }
        }

        // Recursive call for the next row and next column
        reducer(mat, currentRow + 1, currentCol + 1, rref, verbose);
    }
}

/*
 *
 * DETERMINANTS
 *
*/

// Concatenates two matrices horizontally
Matrix Matrix::concat(const Matrix& other) const {
    if (this->matrix == other.matrix) {
        throw CONCAT_ERROR();
    }

    Matrix newMatrix = Matrix(this->m, this->n + other.n);

    for (int i = 0; i < newMatrix.m; i++) {
        for (int j = 0; j < newMatrix.n; j++) {
            if (j < this->n) {
                newMatrix.matrix[i][j] = this->matrix[i][j];
            }
            else {
                newMatrix.matrix[i][j] = other.matrix[i][j - this->n];
            }
        }
    }

    return newMatrix;
}

// Returns a submatrix of the current matrix
// Inclusive of row_begin and col_begin, exclusive of row_end and col_end
Matrix Matrix::submatrix(int row_begin, int col_begin, int row_end, int col_end) const {
    Matrix newMatrix(row_end - row_begin, col_end - col_begin);

    for (int i = row_begin; i < row_end; i++) {
        for (int j = col_begin; j < col_end; j++) {
            newMatrix.matrix[i - row_begin][j - col_begin] = this->matrix[i][j];
        }
    }

    return newMatrix;
}

// Returns the transposed of the current matrix
Matrix Matrix::transpose() const {
    Matrix newMatrix = Matrix(this->n, this->m);

    for (int i = 0; i < newMatrix.m; i++) {
        for (int j = 0; j < newMatrix.n; j++) {
            newMatrix.matrix[i][j] = this->matrix[j][i];
        }
    }

    return newMatrix;
}