#include <iostream>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include "IdentityMatrix.hpp"

using namespace std;

int main(void) {
    Matrix m1 = Matrix(3,3);
    SquareMatrix m2 (m1);

    m1.load("0 1 2 1 0 3 4 -3 8");

    cout << m1 << endl;

    cout << m2 << endl;

    cout << m2.inverse() << endl;
}