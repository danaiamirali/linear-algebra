#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.h
 * Class containing definition of a matrix
 * Maximimum size of 10 rows and 10 columns
*/

#include <iostream>


class Matrix {
    int m, n;
    int MAX_DIM = 10;
    int matrix[10][10] {};
    public:
        Matrix(int m_in, int n_in):
        m (m_in), n(n_in) {}


};

#endif // Matrix

#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

/* Matrix.h
 * Class containing definition of a matrix
 * Maximimum size of 10 rows and 10 columns
*/

#include <iostream>


class Matrix {
    int m, n;
    int MAX_DIM = 10;
    int matrix[10][10] {};
    public:
        Matrix(int m_in, int n_in):
        m (m_in), n(n_in) {}

        
};

#endif // Matrix