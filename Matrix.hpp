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

    int m, n;
    int **matrix = nullptr;

        // Converts 1D Index to 2D Index
        std::pair<int, int> index(int i) const {
            return std::pair<int, int> (i / n, i % n);
        }

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

class SquareMatrix : public Matrix {
    public:
        SquareMatrix(int n) : Matrix(n, n) {}

        // Calculates determinant of matrix
        int determinant() {
            if ()
        }
};

#endif // Matrix