//
// Created by federico on 27/08/16.
//

#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix<float> mat(5, 5);

    mat.setAllValues(1);
    mat.setValue(3, 1, 9.2f);
    mat(2, 2) = 7;
    mat(3, 4) = 7;
    float value = mat(3, 1);


    Matrix<float> row = mat.getRow(2);
    row(0, 4) = 3.5f;
    mat.setRow(0, row);

    Matrix<float> trasposta = mat.transpose();
    Matrix<float> subMat = mat.subMatrix(0, 0);
    float determinante = mat.determinant();

    cout << "mat: " << mat.toString() << endl;
    cout << "determinante: " << determinante << endl;
    cout << "trasposta: " << trasposta.toString() << endl;
    cout << "subMat: " << subMat.toString() << endl;
}