#include <iostream>
#include "Matrix.hpp"
#include "IdentityMatrix.hpp"

using namespace std;

int main(void) {
    Matrix m1(3,3);

    IdentityMatrix im(3);

    m1.load("20 50 30 2 10 6 4 5 0");

    cout << "m1:" << endl;
    cout << m1 << endl;
    

    cout << "m1 doubled:" << endl;
    cout << m1 * 2 << endl;

    cout << "m1 x identity:" << endl;
    cout << m1 * im << endl;

    cout << "m1 reduced:" << endl;
    cout << m1.ref() << endl;
}