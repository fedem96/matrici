//
// Created by federico on 02/09/16.
//

#include "gtest/gtest.h"
#include "../Row.h"

TEST(Row, GetterAndSetter)
{
    Row<int> r1(3);
    r1.setValue(0, 5);
    r1.setValue(1, 7);
    r1.setValue(2, 9);

    int values[3] = {5, 7, 9};
    Row<int> r2(3, values);

    ASSERT_EQ(r1.getValue(0), r2.getValue(0));
    ASSERT_EQ(r1.getValue(1), r2.getValue(1));
    ASSERT_EQ(r1.getValue(2), r2.getValue(2));

    ASSERT_THROW(r1.setValue(-1, 0), out_of_range);
    ASSERT_THROW(r2.setValue(3, 0), out_of_range);
}

TEST(Row, AddingValues)
{
    Row<int> r(0);
    r.pushValue(1);
    r.pushValue(2);
    r.insertValue(0, 3);
    r.insertValue(3, 4);

    ASSERT_EQ(r.getValue(0), 3);
    ASSERT_EQ(r.getValue(1), 1);
    ASSERT_EQ(r.getValue(2), 2);
    ASSERT_EQ(r.getValue(3), 4);
    ASSERT_EQ(r.getWidth(), 4);

    ASSERT_THROW(r.insertValue(5, 5), out_of_range);
}

TEST(Row, RemovingValues)
{
    double values[4] = {0.1, 0.2, 0.35, 0.47};
    Row<double> r(4, values);
    r.removeValue(1);
    r.removeValue(1);

    ASSERT_EQ(r.getValue(0), 0.1);
    ASSERT_EQ(r.getValue(1), 0.47);

    ASSERT_EQ(r.getWidth(), 2);

    ASSERT_THROW(r.removeValue(2), out_of_range);
}

TEST(Row, Operators)
{
    Row<int> r1(3);
    r1.setValue(0, 5);
    r1.setValue(1, 7);
    r1(2) =  9;

    int values[3] = {5, 7, 9};
    Row<int> r2(3, values);

    ASSERT_EQ(r1, r2);

    r2(2) = 10;
    ASSERT_NE(r1, r2);

    ASSERT_THROW(r1(3), out_of_range);
    ASSERT_THROW(r2(-1) = 0, out_of_range);
}