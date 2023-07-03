#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.hpp"

class SquareMatrix : public Matrix {

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
};

#endif // SQUAREMATRIX_H