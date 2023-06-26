#include <iostream>
#include "Matrix.hpp"
#include "IdentityMatrix.hpp"

using namespace std;

int main(void) {
    Matrix m1(5,3);

    IdentityMatrix im(3);

    m1.load();

    cout << "m1:" << endl;
    cout << m1 << endl;
    

    cout << "m1 doubled:" << endl;
    cout << m1 * 2 << endl;

    cout << "m1 x identity:" << endl;
    cout << m1 * im << endl;

    cout << "rref(m1):" << endl;
    cout << m1.rref(true) << endl;

    cout << "ref(m1):" << endl;
    cout << m1.ref() << endl;
}