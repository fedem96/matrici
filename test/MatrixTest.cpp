//
// Created by federico on 29/08/16.
//

#include "gtest/gtest.h"
#include "../Matrix.h"

TEST(Matrix, Constructor)
{
    const int defValue = 11;
    Matrix<int> m(6, 9);
    m.setAllValues(defValue);
    ASSERT_EQ(m.getNumRows(), 6);
    ASSERT_EQ(m.getNumColumns(), 9);
    ASSERT_EQ(m.getValue(1,1), defValue);
    ASSERT_EQ(m.getValue(2,3), defValue);
    ASSERT_EQ(m.getValue(4,7), defValue);
}

TEST(Matrix, Operators)
{
    Matrix<int> m1(4, 3), m2(3, 2), m3(4, 3), m4(4, 3), m5(4, 2);
    m1.setAllValues(0);
    m2.setAllValues(1);
    m3.setAllValues(0);
    m4.setAllValues(0);
    m5.setAllValues(0);
    m1.setValue(3, 2, 4);
    m3.setValue(3, 2, 4);

    // operator ==
    ASSERT_EQ(m1, m3);

    // operator !=
    ASSERT_NE(m1, m2);
    m3.setValue(1, 1, 1);
    ASSERT_NE(m1, m3);

    // operator =
    m1 = m3;
    ASSERT_EQ(m1, m3);

    // operator -
    ASSERT_EQ(m1 - m3, m4);
    ASSERT_THROW(m1 - m2, std::invalid_argument);

    // operator +
    m4.setValue(3, 2, 8);
    m4.setValue(1, 1, 2);
    ASSERT_EQ(m1 + m3, m4);
    ASSERT_THROW(m1 + m2, std::invalid_argument);

    // operator * (scalar)
    m4.setValue(3, 2, 20);
    m4.setValue(1, 1, 5);
    ASSERT_EQ(m1 * 5, m4);

    // operator *
    ASSERT_THROW(m1 * m3, std::invalid_argument);
    m2.setValue(2, 1, 2);
    m5.setValue(1, 0, 1);
    m5.setValue(1, 1, 1);
    m5.setValue(3, 0, 4);
    m5.setValue(3, 1, 8);
    ASSERT_EQ(m1 * m2, m5);

    // operator ()
    ASSERT_EQ(m1.getValue(3, 1), m1(3, 1));
    ASSERT_THROW(m1(3, 3), std::out_of_range);
    m1(1, 2) = 96;
    ASSERT_EQ(m1(1, 2), 96);
}

TEST(Matrix, Transpose)
{
    Matrix<float> mat(3, 2);
    mat.setAllValues(0);
    mat.setValue(1, 1, 1);
    mat.setValue(2, 1, 3);
    Matrix<float> trMat = mat.transpose();

    ASSERT_EQ(trMat.getNumRows(), 2);
    ASSERT_EQ(trMat.getNumColumns(), 3);
    ASSERT_EQ(trMat.getValue(0,0), 0);
    ASSERT_EQ(trMat.getValue(1,1), 1);
    ASSERT_EQ(trMat.getValue(1,2), 3);
}

TEST(Matrix, SubMatrix)
{
    Matrix<int> mat(4, 3);
    mat.setAllValues(1);
    mat.setValue(0, 0, 0);
    mat.setValue(2, 0, 3);
    mat.setValue(1, 1, 4);
    mat.setValue(3, 2, 5);

    Matrix<int> subMat = mat.subMatrix(2, 1);
    ASSERT_EQ(subMat.getValue(0, 0), 0);
    ASSERT_EQ(subMat.getValue(1, 1), 1);
    ASSERT_EQ(subMat.getValue(2, 1), 5);
}

TEST(Matrix, Determinant)
{
    Matrix<int> errMat(3, 2);
    ASSERT_THROW(errMat.determinant(), std::logic_error);

    Matrix<int> mat(3, 3);
    mat.setAllValues(1);
    mat.setValue(0, 0, 5);
    mat.setValue(0, 2, 2);
    mat.setValue(1, 1, 17);
    mat.setValue(2, 2, 6);
    ASSERT_EQ(mat.determinant(), 468);
}

TEST(Matrix, RowsAndColumns)
{
    Matrix<int> m(2, 3);
    m.setAllValues(0);
    int rVal[3] = {1, 2, 3};
    m.pushRow(Matrix<int>(1, 3, rVal));
    rVal[0] = 0;
    rVal[1] = 10;
    rVal[2] = 20;
    m.insertRow(2, Matrix<int>(1, 3, rVal));
    ASSERT_EQ(m.getNumRows(), 4);
    ASSERT_EQ(m(2, 1), 10);
    ASSERT_EQ(m(3,2), 3);

    rVal[0] = 4;
    rVal[1] = 17;
    rVal[2] = 23;
    m.setRow(0, Matrix<int>(1, 3, rVal));
    ASSERT_EQ(m(0, 2), 23);

    m(0, 2) = 67;
    Matrix<int> r = m.getRow(0);
    ASSERT_EQ(r.getNumColumns(), 3);
    ASSERT_EQ(r(0, 2), 67);

    int cVal[4] = {11, 22, 33, 44};
    m.pushColumn(Matrix<int>(4, 1, cVal));
    cVal[0] = 0;
    cVal[1] = 100;
    cVal[2] = 200;
    cVal[2] = 300;
    m.insertColumn(1, Matrix<int>(4, 1, cVal));
    ASSERT_EQ(m.getNumColumns(), 5);
    ASSERT_EQ(m(3, 4), 44);
    ASSERT_EQ(m(1, 1), 100);

    cVal[0] = 7;
    cVal[1] = 19;
    cVal[2] = 24;
    cVal[3] = 38;
    m.setColumn(1, Matrix<int>(4, 1, cVal));
    ASSERT_EQ(m(1, 1), 19);

    Matrix<int> c = m.getColumn(3);
    ASSERT_EQ(c.getNumRows(), 4);
    ASSERT_EQ(c(1, 0), 0);

    std::cout << m.toString() << std::endl;
    m.removeRow(1);
    std::cout << m.toString() << std::endl;
    ASSERT_EQ(m(1, 2), 10);
    m.removeColumn(2);
    std::cout << m.toString() << std::endl;
    ASSERT_EQ(m(1, 2), 20);

}