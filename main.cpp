//
// Created by federico on 27/08/16.
//

#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix<int> m(5, 5);
    cout << m.toString() << endl;
    m.setValue(3, 1, 1);
    cout << m.toString() << endl;
}