//
// Created by federico on 28/08/16.
//

#ifndef MATRICI_MATRIX_H
#define MATRICI_MATRIX_H

#include <string>

template <typename t>
class Matrix
{
public:
    Matrix(int width, int height);
    Matrix(const Matrix<t> &other);
    ~Matrix();

    int getWidth() const;
    int getHeight() const;

    void setValue(const t &value, int rowIndex, int columnIndex);
    t getValue(int rowIndex, int columnIndex) const;

    t* getRow(int rowIndex) const;
    t* getColumn(int columnIndex) const;

    Matrix operator = (const Matrix &other) const;
    Matrix operator + (const Matrix &other) const;
    Matrix operator - (const Matrix &other) const;
    Matrix operator * (const Matrix &other) const;

    t determinant() const;
    Matrix transpose () const;

    std::string toString() const;

private:
    int width, height;
    t *data;
};

template <typename t>
Matrix<t>::Matrix(int width, int height) : width(width), height(height)
{
    data = new t[width * height];
}

template <typename t>
Matrix<t>::Matrix(const Matrix<t> &other) : Matrix(other.width, other.height)
{
    for(int col = 0; col < width; col++)
        for(int row = 0; row < height; row++)
            data[col + row*width] = other.data[col + row*width];
}

template <typename t>
Matrix<t>::~Matrix()
{
    delete []data;
}

template <typename t>
int Matrix<t>::getWidth() const
{
    return width;
}

template <typename t>
int Matrix<t>::getHeight() const
{
    return height;
}

template <typename t>
void Matrix<t>::setValue(const t &value, int rowIndex, int columnIndex)
{
    data[rowIndex + columnIndex*width] = value;
}

template <typename t>
t Matrix<t>::getValue(int rowIndex, int columnIndex) const
{
    return data[rowIndex + columnIndex*width];
}



template <typename t>
std::string Matrix<t>::toString() const
{
    std::string toReturn = "Matrix object, " + std::to_string(height) + " rows, " + std::to_string(width) + " columns:\n";
    for(int row = 0; row < height; row++)
    {
        toReturn += "\t";
        for(int col = 0; col < width; col++)
            toReturn += " " + std::to_string(data[row + col*width]);
        toReturn += "\n";
    }
    return toReturn;
}


#endif //MATRICI_MATRIX_H
