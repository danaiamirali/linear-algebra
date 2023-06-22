#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main(void) {
    Matrix m1(3,4);
    Matrix m2(3,3);

    m1.load("1 2 3 6 2 -3 2 14 3 1 -1 -2");
    m2.load();

    cout << "m1:" << endl;
    cout << m1 << endl;

    cout << "m1 reduced:" << endl;
    cout << m1.ref() << endl;
}