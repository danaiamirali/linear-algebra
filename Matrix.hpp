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
    int **matrix = nullptr; // Mutable pointer - cursor
    int ** const root; // Immutable pointer - root of matrix

    public:


        /*
         * ========================
         *       CONSTRUCTORS
         * ========================
        */

        // Default constructor
        // Creates 2x2 matrix
        Matrix() : m(2), n(2), matrix(new int*[m]), root(matrix) {}


        // Constructor with specified dimensions
        // Dynamically allocates memory for matrix
        // Throws DIM_ERROR if dimensions are invalid
        Matrix(int m_in, int n_in):
        m (m_in), n(n_in), matrix(new int*[m]), root(matrix) {

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
        : m(matrix.m), n(matrix.n), matrix(new int*[m]), root(matrix.root){
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
       Matrix operator*(const Matrix &other) const {
            if (this->n != other.m) {
                throw MULTIPLY_ERROR();
            }

            Matrix newMatrix = Matrix(this->m, other.n);

            for (int i = 0; i < newMatrix.m; i++) {
                for (int j = 0; j < newMatrix.n; j++) {
                    int sum = 0;
                    for (int k = 0; k < this->n; k++) {
                        sum += this->matrix[i][k] * other.matrix[k][j];
                    }
                    newMatrix.matrix[i][j] = sum;
                }
            }

            return newMatrix;
       }

       // Scalar multiplication
       Matrix operator*(const int c) const {
            Matrix newMatrix = Matrix(this->m, this->n);

            for (int i = 0; i < newMatrix.m; i++) {
                for (int j = 0; j < newMatrix.n; j++) {
                        newMatrix.matrix[i][j] = this->matrix[i][j] * c;
                }
            }

            return newMatrix;
       }


        // Reduced Echelon Form
        // Returns a new matrix

        // Is top left corner 0?
            //   - If yes, look down until non-zero and this->swapRow()
            //      - If no non-zero found, move right and repeat
            //  - If no, perform scalar multiplication to make it 1
            //  - Perform row operations to make rest of column 0
            //  - Crop first row and first col and repeat
        

    private:
        /*
         * ========================
         *     PRIVATE HELPERS
         * ========================
        */ 

       void resetCursor() const {
           int** temp = const_cast<int**>(root);
           *matrix = *temp;
       }

        Matrix *shiftCursor(int row, int col) {
            *matrix = matrix[row];
            *matrix = *matrix + col;

            return this;
        }

        // Converts 1D Index to 2D Index
        std::pair<int, int> index(int i) const {
            return std::pair<int, int> (i / n, i % n);
        }


        int* getRow(int row) const {
            return matrix[row];
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
                    delete[] matrix[i];
                }
                delete[] matrix;
            }


};

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
        int determinant() {
            /*
            TO-DO
            */

           return 0;
        }
};

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

#endif // Matrix
