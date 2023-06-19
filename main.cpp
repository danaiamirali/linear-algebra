#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main(void) {
    Matrix m1(3,3);
    Matrix m2(3,3);

    m1.load();
    m2.load();

    cout << "m1:" << endl;
    cout << m1 << endl;

    cout << "m2:" << endl;
    cout << m2 << endl;
}