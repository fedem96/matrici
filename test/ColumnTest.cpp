//
// Created by federico on 02/09/16.
//

#include "gtest/gtest.h"
#include "../Column.h"

TEST(Column, GetterAndSetter)
{
    Column<int> c1(3);
    c1.setValue(0, 8);
    c1.setValue(1, 7);
    c1.setValue(2, 0);

    int values[3] = {8, 7, 0};
    Column<int> c2(3, values);

    ASSERT_EQ(c1.getValue(0), c2.getValue(0));
    ASSERT_EQ(c1.getValue(1), c2.getValue(1));
    ASSERT_EQ(c1.getValue(2), c2.getValue(2));

    ASSERT_THROW(c1.setValue(-2, 0), out_of_range);
    ASSERT_THROW(c2.setValue(3, 0), out_of_range);
}

TEST(Column, AddingValues)
{
    Column<int> c(0);
    c.pushValue(10);
    c.pushValue(9);
    c.insertValue(0, 8);
    c.insertValue(3, 7);

    ASSERT_EQ(c.getValue(0), 8);
    ASSERT_EQ(c.getValue(1), 10);
    ASSERT_EQ(c.getValue(2), 9);
    ASSERT_EQ(c.getValue(3), 7);
    ASSERT_EQ(c.getHeight(), 4);

    ASSERT_THROW(c.insertValue(5, 0), out_of_range);
}

TEST(Column, RemovingValues)
{
    double values[4] = {0.01, 2.9, 3.5, 0.4};
    Column<double> c(4, values);
    c.removeValue(3);
    c.removeValue(1);

    ASSERT_EQ(c.getValue(0), 0.01);
    ASSERT_EQ(c.getValue(1), 3.5);

    ASSERT_EQ(c.getHeight(), 2);

    ASSERT_THROW(c.removeValue(2), out_of_range);
}

TEST(Column, Operators)
{
    Column<int> c1(3);
    c1.setValue(0, 5);
    c1.setValue(1, 7);
    c1(2) =  9;

    int values[3] = {5, 7, 9};
    Column<int> c2(3, values);

    ASSERT_EQ(c1, c2);

    c2(2) = 10;
    ASSERT_NE(c1, c2);

    ASSERT_THROW(c1(3), out_of_range);
    ASSERT_THROW(c2(-1) = 0, out_of_range);
}