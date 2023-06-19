#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.h
 * Class containing definition of a matrix
 * Maximimum size of 10 rows and 10 columns
*/

#include <iostream>

const int MAX_DIM = 20;

class DIM_ERROR {
    public:
        DIM_ERROR() {
            std::cout << "Error: Invalid dimensions" << std::endl;
        }
};

class Matrix {
    /*
    INVARIANTS:
    m and n must be positive integers
    m and n must be less than MAX_DIM
    */

    int m, n;
    int **matrix = nullptr;

    public:
        // Constructor with specified dimensions
        // Dynamically allocates memory for matrix
        // Throws DIM_ERROR if dimensions are invalid
        Matrix(int m_in, int n_in):
        m (m_in), n(n_in) {

            if (m <= 0 || n <= 0 || m > MAX_DIM || n > MAX_DIM) {
                throw DIM_ERROR();
            }

            matrix = new int*[m];
            for (int i = 0; i < m; i++) {
                matrix[i] = new int[n];
            }
        }

        // Default constructor
        Matrix() : m(0), n(0) {}

        ~Matrix() {
            for (int i = 0; i < m; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

        // Fills matrix with random integers from 0 to 9
        Matrix *load() {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = rand() % 10;
                }
            }

            return this;
        }

        int* operator[](int i) const {
            return matrix[i];
        }
        
        friend std::ostream& operator<<(std::ostream &os, const Matrix& matrix) {
            for (int i = 0; i < matrix.m; i++) {
                os << "| ";
                for (int j = 0; j < matrix.n; j++) {
                    os << matrix[i][j] << " ";
                }
                os << "|" << std::endl;
            }

            return os;
        }

};

#endif // Matrix