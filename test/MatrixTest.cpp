//
// Created by federico on 29/08/16.
//

#include "gtest/gtest.h"
#include "../Matrix.h"

TEST(Matrix, Constructor)
{
    const int defValue = 11;
    Matrix<int> m(6, 9, defValue);
    ASSERT_EQ(m.getNumRows(), 6);
    ASSERT_EQ(m.getNumColumns(), 9);
    ASSERT_EQ(m.getValue(1,1), defValue);
    ASSERT_EQ(m.getValue(2,3), defValue);
    ASSERT_EQ(m.getValue(4,7), defValue);
}

TEST(Matrix, Operators)
{
    Matrix<int> m1(4, 3, 0), m2(3, 2, 1), m3(4, 3, 0), m4(4, 3, 0), m5(4, 2, 0);
    m1.setValue(4, 3, 2);
    m3.setValue(4, 3, 2);

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
    m4.setValue(8, 3, 2);
    m4.setValue(2, 1, 1);
    ASSERT_EQ(m1 + m3, m4);
    ASSERT_THROW(m1 + m2, std::invalid_argument);

    // operator * (scalar)
    m4.setValue(20, 3, 2);
    m4.setValue(5, 1, 1);
    ASSERT_EQ(m1 * 5, m4);

    // operator *
    ASSERT_THROW(m1 * m3, std::invalid_argument);
    m2.setValue(2, 2, 1);
    m5.setValue(1, 1, 0);
    m5.setValue(1, 1, 1);
    m5.setValue(4, 3, 0);
    m5.setValue(8, 3, 1);
    ASSERT_EQ(m1 * m2, m5);
}

TEST(Matrix, Transpose)
{
    Matrix<float> mat(3, 2, 0);
    mat.setValue(1, 1, 1);
    mat.setValue(3, 2, 1);
    Matrix<float> trMat = mat.transpose();

    ASSERT_EQ(trMat.getNumRows(), 2);
    ASSERT_EQ(trMat.getNumColumns(), 3);
    ASSERT_EQ(trMat.getValue(0,0), 0);
    ASSERT_EQ(trMat.getValue(1,1), 1);
    ASSERT_EQ(trMat.getValue(1,2), 3);
}

TEST(Matrix, SubMatrix)
{
    Matrix<int> mat(4, 3, 1);
    mat.setValue(0, 0, 0);
    mat.setValue(3, 2, 0);
    mat.setValue(4, 1, 1);
    mat.setValue(5, 3, 2);

    Matrix<int> subMat = mat.subMatrix(2, 1);
    ASSERT_EQ(subMat.getValue(0, 0), 0);
    ASSERT_EQ(subMat.getValue(1, 1), 1);
    ASSERT_EQ(subMat.getValue(2, 1), 5);
}

TEST(Matrix, Determinant)
{
    Matrix<int> errMat(3, 2);
    ASSERT_THROW(errMat.determinant(), std::logic_error);

    Matrix<int> mat(3, 3, 1);
    mat.setValue(5, 0, 0);
    mat.setValue(2, 0, 2);
    mat.setValue(17, 1, 1);
    mat.setValue(6, 2, 2);
    ASSERT_EQ(mat.determinant(), 468);
}