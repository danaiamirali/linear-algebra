#include <iostream>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include "IdentityMatrix.hpp"

using namespace std;

int main(void) {
    std::string matrix = "2 3 4 -3 -3 -2 -2 1 -1";
    Matrix m1 = Matrix(3,3, matrix);
    SquareMatrix m2 (m1);

    cout << m1 << endl;

    cout << m2 << endl;

    cout << m2.inverse() << endl;

    cout << m2 * m2.inverse() << endl;

    cout << m1.transpose() << endl;
}