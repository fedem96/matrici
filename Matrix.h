//
// Created by federico on 28/08/16.
//

#ifndef MATRICI_MATRIX_H
#define MATRICI_MATRIX_H

#include <string>
#include <stdexcept>

template <typename t>
class Matrix
{
public:
    Matrix(int numRows, int numColumns);
    Matrix(int numRows, int numColumns, t defaultValue);
    Matrix(const Matrix<t> &other);
    ~Matrix();

    int getNumColumns() const;
    int getNumRows() const;

    void setValue(const t &value, int rowIndex, int columnIndex);
    t getValue(int rowIndex, int columnIndex) const;

    /*t* getRow(int rowIndex) const;
    t* getColumn(int columnIndex) const;*/

    bool operator == (const Matrix &other) const;
    bool operator != (const Matrix &other) const;
    Matrix<t> operator = (const Matrix<t> &other);
    Matrix<t> operator + (const Matrix<t> &other) const throw(std::invalid_argument);
    Matrix<t> operator - (const Matrix<t> &other) const throw(std::invalid_argument);
    Matrix<t> operator * (const Matrix<t> &other) const throw(std::invalid_argument);
    Matrix<t> operator * (const t &scalar) const;

    Matrix<t> subMatrix(int deletingRow, int deletingColumn) const throw(std::logic_error, std::out_of_range);
    t determinant() const throw(std::logic_error);
    Matrix transpose () const;

    std::string toString() const;

private:
    int numRows, numColumns;
    t *data;
};

template <typename t>
Matrix<t>::Matrix(int numRows, int numColumns) : numRows(numRows), numColumns(numColumns)
{
    data = new t[numRows * numColumns];
}

template <typename t>
Matrix<t>::Matrix(int numRows, int numColumns, t defaultValue) : Matrix(numRows, numColumns)
{
    for(int col = 0; col < numColumns; col++)
        for(int row = 0; row < numRows; row++)
            data[col + row*numColumns] = defaultValue;
}

template <typename t>
Matrix<t>::Matrix(const Matrix<t> &other) : Matrix(other.numRows, other.numColumns)
{
    for(int col = 0; col < numColumns; col++)
        for(int row = 0; row < numRows; row++)
            data[col + row*numColumns] = other.data[col + row*numColumns];
}

template <typename t>
Matrix<t>::~Matrix()
{
    delete []data;
}

template <typename t>
int Matrix<t>::getNumRows() const
{
    return numRows;
}

template <typename t>
int Matrix<t>::getNumColumns() const
{
    return numColumns;
}

template <typename t>
void Matrix<t>::setValue(const t &value, int rowIndex, int columnIndex)
{
    data[columnIndex + rowIndex*numColumns] = value;
}

template <typename t>
t Matrix<t>::getValue(int rowIndex, int columnIndex) const
{
    return data[columnIndex + rowIndex*numColumns];
}

/*template <typename t>
t* Matrix<t>::getRow(int rowIndex) const
{
    return nullptr;
}

template <typename t>
t* Matrix<t>::getColumn(int columnIndex) const
{
    return nullptr;
}*/

template <typename t>
bool Matrix<t>::operator==(const Matrix<t> &other) const
{
    if(numRows != other.numRows || numColumns != other.numColumns)
        return false;
    for(int i = 0; i < numRows*numColumns; i++)
        if(data[i] != other.data[i])
            return false;
    return true;
}

template <typename t>
bool Matrix<t>::operator!=(const Matrix<t> &other) const
{
    return ! (*this == other);
}

template <typename t>
Matrix<t> Matrix<t>::operator=(const Matrix<t> &other)
{
    if(this != &other)
    {
        this->~Matrix();
        numRows = other.numRows;
        numColumns = other.numColumns;
        data = new t[numRows*numColumns];
        for(int i = 0; i < numRows*numColumns; i++)
            data[i] = other.data[i];
    }
    return *this;
}

template <typename t>
Matrix<t> Matrix<t>::operator+(const Matrix<t> &other) const throw(std::invalid_argument)
{
    if(numRows != other.numRows || numColumns != other.numColumns)
        throw std::invalid_argument("Dimensioni matrici differenti");

    Matrix<t> result(numRows, numColumns);
    for(int i = 0; i < numRows*numColumns; i++)
        result.data[i] =  data[i] + other.data[i];
    return result;
}

template <typename t>
Matrix<t> Matrix<t>::operator-(const Matrix<t> &other) const throw(std::invalid_argument)
{
    if(numRows != other.numRows || numColumns != other.numColumns)
        throw std::invalid_argument("Dimensioni matrici differenti");

    Matrix<t> result(numRows, numColumns);
    for(int i = 0; i < numRows*numColumns; i++)
        result.data[i] =  data[i] - other.data[i];
    return result;
}

template <typename t>
Matrix<t> Matrix<t>::operator*(const Matrix<t> &other) const throw(std::invalid_argument)
{
    if(numColumns != other.numRows)
        throw std::invalid_argument("Dimensioni non congrue per prodotto");

    Matrix<t> result(numRows, other.numColumns, 0);
    for(int row = 0; row < numRows; row++)
        for(int col = 0; col < other.numColumns; col++)
            for (int i = 0; i < numColumns; i++)
                result.data[col + row*other.numColumns] += data[i + row*numColumns] * other.data[col + i*other.numColumns];

    return result;
}

template <typename t>
Matrix<t> Matrix<t>::operator*(const t &scalar) const
{
    Matrix<t> result(numRows, numColumns);
    for(int i = 0; i < numColumns*numRows; i++)
        result.data[i] =  data[i] * scalar;
    return result;
}

template <typename t>
Matrix<t> Matrix<t>::subMatrix(int deletingRow, int deletingColumn) const throw(std::logic_error, std::out_of_range)
{
    if(numRows <= 1 || numColumns <= 1)
        throw std::logic_error("Matrice troppo piccola per estrarre una sottomatrice");

    if(deletingRow < 0 || deletingRow >= numRows || deletingColumn < 0 || deletingColumn >= numColumns)
        throw std::out_of_range("Indici di riga e/o colonna non validi");

    Matrix<t> result(numRows-1, numColumns-1);

    for(int col = 0; col < numColumns; col++)
    {
        if(col == deletingColumn)
            continue;
        for(int row = 0; row < numRows; row++)
        {
            if(row == deletingRow)
                continue;
            int index = (col > deletingColumn ? col-1 : col) + (row > deletingRow ? row-1 : row)*result.numColumns;
            result.data[index] = data[col + row*numColumns];
        }
    }

    return result;
}


template <typename t>
t Matrix<t>::determinant() const throw(std::logic_error)
{
    if(numRows != numColumns)
        throw std::logic_error("Impossibile calcolare il determinante su una matrice non quadrata");

    if(numRows == 2)
        return data[0]*data[3] - data[1]*data[2];

    t det = 0;

    for(int col = 0; col < numColumns; col++)
        det += data[col] * subMatrix(0, col).determinant() * (col%2 == 0 ? 1 : -1);

    return det;
}

template <typename t>
Matrix<t> Matrix<t>::transpose() const
{
    Matrix<t> result(numColumns, numRows);

    for(int row = 0; row < numRows; row++)
        for(int col = 0; col < numColumns; col++)
            result.data[row + col*numRows] = data[col + row*numColumns];

    return result;
}

template <typename t>
std::string Matrix<t>::toString() const
{
    std::string toReturn = "Matrix object, " + std::to_string(numRows) + " rows, " + std::to_string(numColumns) + " columns:\n";
    for(int row = 0; row < numRows; row++)
    {
        toReturn += "\t";
        for(int col = 0; col < numColumns; col++)
            toReturn += " " + std::to_string(data[col + row*numColumns]);
        toReturn += "\n";
    }
    return toReturn;
}


#endif //MATRICI_MATRIX_H
