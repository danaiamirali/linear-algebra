#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.h
 * Class containing definition of a matrix
 * Maximimum size of 20 rows and 20 columns
 * Matrices are dynamically allocated and have immutable dimensions
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Fraction.hpp"

using std::cout, std::endl;

const int MAX_DIM = 20;

class DIM_ERROR {
    public:
        DIM_ERROR() {
            cout << "Error: Invalid dimensions" << endl;
        }
};

class MULTIPLY_ERROR {
    public:
        MULTIPLY_ERROR() {
            cout << "Error: Cannot multiply matrices" << endl;
        }
};

class Matrix {
    /*
    INVARIANTS:
    m and n must be positive integers
    m and n must be less than MAX_DIM
    m and n cannot be changed after initialization
    */
    protected:
    friend class SquareMatrix;

    // Immutable dimensions
    const int m, n;
    int **const root; // Immutable pointer - root of matrix
    int **matrix = nullptr; // Mutable pointer - cursor
    

    public:


        /*
         * ========================
         *       CONSTRUCTORS
         * ========================
        */

        // Default constructor
        // Creates 2x2 matrix
        Matrix() : m(2), n(2), root(new int*[m]), matrix(root) {}


        // Constructor with specified dimensions
        // Dynamically allocates memory for matrix
        // Throws DIM_ERROR if dimensions are invalid
        Matrix(int m_in, int n_in):
        m (m_in), n(n_in), root(new int*[m]), matrix(root) {

            if (m <= 0 || n <= 0 || m > MAX_DIM || n > MAX_DIM) {
                throw DIM_ERROR();
            }

            for (int i = 0; i < m; i++) {
                matrix[i] = new int[n];
            }

            cout << m << " x " << n << " matrix initialized." << endl;

        }

        
        // Copy constructor
        // Deep Copy
        Matrix(const Matrix& matrix) 
        : m(matrix.m), n(matrix.n), root(new int*[m]), matrix(root) {
            copyAll(matrix);
        }


        ~Matrix() {
            deleteMatrix();
        }


        /*
         * ========================
         *      PUBLIC METHODS
         * ========================
        */


        std::pair<int, int> getDimensions() const {
            return std::pair<int, int> (m, n);
        }


        // Fills matrix with random integers from 0 to 9
        Matrix *load() {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    root[i][j] = rand() % 10;
                }
            }

            cout << "Successfully loaded matrix with random integers." << endl;

            return this;
        }


        // Fills matrix with integers from string
        // Integers must be separated by spaces
        Matrix *load(std::string nums) {
            std::vector<int> numbers;
            std::stringstream ss(nums);
            std::string token;

            while (ss >> token) {
                try {
                    int num = std::stoi(token);
                    numbers.push_back(num);
                } catch (const std::exception& e) {

                }

            }

            int numbersCount = numbers.size();
            for (int i = 0; i < m * n && i < numbersCount; i++) {
                std::pair<int, int> ind = index(i);
                root[ind.first][ind.second] = numbers[i];
            }

            cout << "Successfully loaded matrix from string." << endl;
    
            return this;
        }


        /*
         * ========================
         *         OPERATORS
         * ========================
        */


        // Overloaded bracket operator
        // Returns pointer to row
        int* operator[](int i) const {
            return root[i];
        }
        

        // Overloaded extraction operator  
        friend std::ostream& operator<<(std::ostream &os, const Matrix& matrix) {
            for (int i = 0; i < matrix.m; i++) {
                os << "| ";
                for (int j = 0; j < matrix.n; j++) {
                    os << matrix[i][j] << " ";
                }
                os << "|" << endl;
            }

            return os;
        }


        /*
         * ========================
         *     MATRIX OPERATIONS
         * ========================
        */

        // Multiplies two matrices
        // Returns new matrix
        Matrix operator*(const Matrix &other) const;

        // Scalar multiplication
        Matrix operator*(int c) const;

        // Matrix reduced echelon form
        // Returns new matrix
        Matrix ref() const;
        void refHelper(int m, int n);
        

    private:
        /*
         * ========================
         *     PRIVATE HELPERS
         * ========================
        */ 

       bool isZeroCol(int col) const {
            for (int i = 0; i < m; i++) {
                if (matrix[i][col] != 0) {
                        return false;
                }
            }

            return true;
       }


       void resetCursor() const {
           int** temp = const_cast<int**>(root);
           *matrix = *temp;
       }

        Matrix *shiftCursor(int row, int col) {
            cout << "Cursor shifted from " << matrix[0][0];
            
            // Shift matrix pointer row number of rows and col number of columns
            int** submatrix = matrix[row];
            cout << *submatrix << endl;
            submatrix[0] = matrix[row] + col;
            cout << **submatrix;

            matrix = submatrix;

            cout << " to " << matrix[0][0] << endl;

            cout << "Matrix following shift: " << endl;
            cout << *this << endl;

            return this;
        }

        // Converts 1D Index to 2D Index
        std::pair<int, int> index(int i) const {
            return std::pair<int, int> (i / n, i % n);
        }


        int* getRow(int row) const {
            return matrix[row];
        }


        void *swapRows(int row1, int row2) {
            if (row1 == row2) {
                return this;
            }

            int *temp = root[row1];
            root[row1] = root[row2];
            root[row2] = temp;
        }

        void *swapRowsFromCursor(int row1, int row2) {
            if (row1 == row2) {
                return this;
            }

            cout << "Swapping rows " << row1 << " and " << row2 << endl;
            int *temp = matrix[row1];
            matrix[row1] = matrix[row2];
            matrix[row2] = temp;
        }


        // Returns new matrix with column x removed
        Matrix popCol(int x) {
            Matrix newMatrix = Matrix(m, n - 1);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == x) {
                        continue;
                    }
                    else if (j < x) {
                        newMatrix[i][j] = matrix[i][j];
                    }
                    else {
                        newMatrix[i][j - 1] = matrix[i][j];
                    }
                }
            }

            return newMatrix;
        }

        // Returns new matrix with first column and row cropped
        Matrix cropFirstColRow() {
            Matrix newMatrix = Matrix(m - 1, n - 1);
            for (int i = 0; i < m - 1; i++) {
                for (int j = 0; j < n - 1; j++) {
                    newMatrix[i][j] = matrix[i + 1][j + 1];
                }
            }

            return newMatrix;
        }

        void subtractRowFromCursor(int row, int subtractor, int cols) {
            for (int i = 0; i < cols; i++) {
                matrix[row][i] -= subtractor * matrix[0][i];
            }
        }

        void divideRowFromCursor(int row, int divisor) {
            for (int i = 0; i < n; i++) {
                matrix[row][i] /= divisor;
            }
        }

        // Performs deep copy from argument matrix to this matrix
        Matrix *copyAll(const Matrix &matrix) {
            for (int i = 0; i < m; i++) {
                this->matrix[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    this->matrix[i][j] = matrix[i][j];
                }
            }

            return this;
        }        


        void deleteMatrix() {
                for (int i = 0; i < m; i++) {
                    delete[] root[i];
                }
                delete[] root;
        }


};



#endif // Matrix
