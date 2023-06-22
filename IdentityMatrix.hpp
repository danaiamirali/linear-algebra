#ifndef IDENTITYMATRIX_H
#define IDENTITYMATRIX_H

#include "SquareMatrix.hpp"

class IdentityMatrix : public SquareMatrix {

    public:

        /*
         * ========================
         *       CONSTRUCTORS
         * ========================
        */

        // Initialize from dimensions
        IdentityMatrix(int n) : SquareMatrix(n) {
            for (int i = 0; i < n; i++) {
                matrix[i][i] = 1;
            }
        }

        // Initialize from Matrix
        IdentityMatrix(Matrix mat) : SquareMatrix(mat) {
            std::pair<int, int> dim = mat.getDimensions();
            if (dim.first != dim.second) {
                throw DIM_ERROR();
            }

            for (int i = 0; i < dim.first; i++) {
                matrix[i][i] = 1;
            }
        }

        int determinant() {
            return 1;
        }

};

#endif // IDENTITYMATRIX_H