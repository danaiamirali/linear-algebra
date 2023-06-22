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
            std::cout << "Error: Invalid dimensions" << std::endl;
        }
};

class Matrix {
    /*
    INVARIANTS:
    m and n must be positive integers
    m and n must be less than MAX_DIM
    m and n cannot be changed after initialization
    */
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
                os << "|" << std::endl;
            }

            return os;
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
                cout << "Base case" << endl;
                return ref;
            }
            // Else: Matrix has more than 1 row
            else {
                cout << "Recursive case" << endl;
                // If first column is all 0s
                if (ref->isZeroCol(0)) {
                    // Skip col and reduce submatrix, then return
                    Matrix mat = ref->cropFirstColRow();
                    return mat.reduce(&mat);
                }
                // If first column has nonzero
                else {
                    // Find first 
                    cout << "First col has nonzero" << endl;
                    int *firstCol = ref->getCol(0);
                    for (int i = 0; i < m; i++) {
                        if (firstCol[i] != 0) {
                            // If first nonzero is not in first row, swap
                            if (i != 0) {
                                cout << "Swapping rows" << endl;
                                ref->swapRows(0, i);
                            }
                            break;
                        }
                    }
                    delete[] firstCol;
                    // Create zeros in all other rows in first column
                    cout << "Creating zeros" << endl;
                    for (int i = 1; i < m; i++) {
                        
                        int *row = ref->getRow(i);
                        if (row[0] == 0) {
                            continue;
                        }

                        cout << "Pointer arithmetic" << endl;
                        // R = R + (-a/b)R1
                        for (int *ptr1 = row, *ptr2 = ref->getRow(0); 
                        ptr1 < row + n; ptr1++, ptr2++) {
                            *ptr1 = *ptr1 + (-row[0] / ref->getRow(0)[0]) * *ptr2;
                        }

                    }

                    Matrix mat = ref->cropFirstColRow();
                    return mat.reduce(&mat);
                }

                return ref;
            }
            // If first column has nonzero
                // Pick first nonzero, if isn't first row, swap with 1st
                // Create zeros in all other rows in first column
            // Reduce submatrix
            // Return
        }


    private:
        /*
         * ========================
         *     PRIVATE HELPERS
         * ========================
        */ 

        // Converts 1D Index to 2D Index
        std::pair<int, int> index(int i) const {
            return std::pair<int, int> (i / n, i % n);
        }


        int* getCol(int col) const {

            int *column = new int[m];
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

#endif // Matrix