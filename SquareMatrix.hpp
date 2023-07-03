#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.hpp"

class NOT_INVERTIBLE {
    public:
        NOT_INVERTIBLE() {
            cout << "Error: Matrix is not invertible" << endl;
        }
};

class SquareMatrix : public Matrix {

    friend class IdentityMatrix;

    public:

        
        /*
         * ========================
         *       CONSTRUCTORS
         * ========================
        */

        // Initialize from dimensions
        SquareMatrix(int n) : Matrix(n, n) {}


        // Initialize from Matrix
        SquareMatrix(Matrix mat) : Matrix(mat.m, mat.m) {

            std::pair<int, int> dim = mat.getDimensions();
            if (dim.first != dim.second) {
                throw DIM_ERROR();
            }

        }


        // Calculates determinant of matrix
        // Intelligently chooses between cofactor expansion and row reduction
        Fraction determinant();

        // Finds inverse of matrix
        SquareMatrix inverse();
};

#endif // SQUAREMATRIX_H