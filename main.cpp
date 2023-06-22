#include <iostream>
#include "Matrix.hpp"
#include "IdentityMatrix.hpp"

using namespace std;

int main(void) {
    Matrix m1(3,4);
    Matrix m2(3,3);

    IdentityMatrix im(4);

    m1.load("1 2 3 6 2 -3 2 14 3 1 -1 -2");
    m2.load();

    cout << "m1:" << endl;
    cout << m1 << endl;
    

    cout << "m1 doubled:" << endl;
    cout << m1 * 2 << endl;

    cout << "m1 x identity:" << endl;
    cout << m1 * im << endl;
}