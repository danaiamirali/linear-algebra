#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.h
 * Class containing definition of a matrix
 * Maximimum size of 20 rows and 20 columns
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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
    friend class SquareMatrix;

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

        // Copy constructor
        // Deep Copy
        Matrix(const Matrix& matrix) {
            copyAll(matrix);
        }

        ~Matrix() {
            deleteMatrix();
        }

        std::pair<int, int> getDimensions() const {
            return std::pair<int, int> (m, n);
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

            return this;
            }

            int numbersCount = numbers.size();
            for (int i = 0; i < m * n && i < numbersCount; i++) {
                std::pair<int, int> ind = index(i);
                matrix[ind.first][ind.second] = numbers[i];
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

        // Overloaded assignment operator
        // Deep Copy
        Matrix *operator=(const Matrix& matrix) {
            if (this == &matrix) {
                return this;
            }

            deleteMatrix();

            copyAll(matrix);
        }

        // Returns reduced echelon form of matrix
        // Does not modify original matrix
        Matrix ref() {
            Matrix ref = *this;

            // Recursively reduce function to echelon form
            return *reduce(&ref);
        }

        Matrix *reduce(Matrix *ref) {
            // Base Case: Matrix has 1 row
            if (ref->m == 1) {
                return ref;
            }
            // Else: Matrix has more than 1 row
            else {
                if (ref->isZeroCol(0)) {
                    return reduce(ref->cropFirstCol());
                }
                else {
                    // Find first nonzero
                    int *firstCol = ref->getCol(0);
                    for (int i = 0; i < m; i++) {
                        if (firstCol[i] != 0) {
                            // If first nonzero is not in first row, swap
                            if (i != 0) {
                                ref->swapRows(0, i);
                            }
                            break;
                        }
                    }
                    // Create zeros in all other rows in first column
                    for (int i = 1; i < m; i++) {
                        // R = R + (-a/b)R1
                        int *row = ref->getRow(i);
                        if (row[0] == 0) {
                            continue;
                        }
                        /*
                        TO-DO
                        */
                    }

                    reduce(ref->cropFirstCol());
                }

                return ref;
            }
            // If first column is all 0s
                // Skip col and reduce submatrix, then return
            // If first column has nonzero
                // Pick first nonzero, if isn't first row, swap with 1st
                // Create zeros in all other rows in first column
            // Reduce submatrix
            // Return
        }

    private:
        /*
         * Helper class functions
        */   

        // Converts 1D Index to 2D Index
        std::pair<int, int> index(int i) const {
            return std::pair<int, int> (i / n, i % n);
        }

        int* getCol(int col) const {
            int *column;
            for (int i = 0; i < m; i++) {
                column[i] = matrix[i][col];
            }

            return column;
        }

        int* getRow(int row) const {
            return matrix[row];
        }

        bool isZeroCol(int col) const {
            int *c = getCol(col);
            for (int i = 0; i < n; i++) {
                if (c[i] != 0) {
                    return false;
                }
            }

            return true;
        }

        Matrix *swapRows(int row1, int row2) {
            int *temp = matrix[row1];
            matrix[row1] = matrix[row2];
            matrix[row2] = temp;

            return this;
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

        // Returns pointer to same matrix with first column cropped
        Matrix *cropFirstCol() {
            for (int i = 0; i < m; i++) {
                matrix[i]++;
            }
            n--;
        }

        Matrix *copyAll(const Matrix &matrix) {
            this->m = matrix.m;
            this->n = matrix.n;

            this->matrix = new int*[m];
            for (int i = 0; i < m; i++) {
                this->matrix[i] = new int[n];
            }

            return this;
        }        

        void deleteMatrix() {
                for (int i = 0; i < m; i++) {
                    delete[] matrix[i];
                }
                delete[] matrix;
            }


};

class SquareMatrix : public Matrix {
    public:
        SquareMatrix(int n) : Matrix(n, n) {}

        SquareMatrix(Matrix m) {
            std::pair<int, int> dim = m.getDimensions();
            if (dim.first != dim.second) {
                throw DIM_ERROR();
            }

            this->n = dim.first;

            this->matrix = m.matrix;
        }

        // Calculates determinant of matrix
        // Intelligently chooses between cofactor expansion and row reduction
        int determinant() {
            
        }
};

#endif // Matrix