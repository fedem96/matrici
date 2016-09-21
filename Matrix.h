//
// Created by federico on 28/08/16.
//

#ifndef MATRICI_MATRIX_H
#define MATRICI_MATRIX_H

#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename t>
class Matrix
{
public:
    Matrix(int numRows, int numColumns);
    Matrix(int numRows, int numColumns, t *values);
    Matrix(const Matrix<t> &other);
    ~Matrix();

    int getNumColumns() const;
    int getNumRows() const;

    void setAllValues(const t &value);
    void setValue(int rowIndex, int columnIndex, const t &value) throw(out_of_range);
    t getValue(int rowIndex, int columnIndex) const throw(out_of_range);

    void pushRow(Matrix<t> row) throw(invalid_argument);
    void pushColumn(Matrix<t> col) throw(invalid_argument);

    void insertRow(int beforeOfIndex, Matrix<t> rowMat) throw(out_of_range, invalid_argument);
    void insertColumn(int beforeOfIndex, Matrix<t> colMat) throw(out_of_range, invalid_argument);

    void setRow(int rowIndex, Matrix<t> rowMat) throw(out_of_range, invalid_argument);
    void setColumn(int columnIndex, Matrix<t> colMat) throw(out_of_range, invalid_argument);

    Matrix<t> getRow(int rowIndex) const throw(out_of_range);
    Matrix<t> getColumn(int columnIndex) const throw(out_of_range);

    void removeRow(int rowIndex) throw(out_of_range);
    void removeColumn(int columnIndex) throw(out_of_range);

    bool operator == (const Matrix &other) const;
    bool operator != (const Matrix &other) const;
    Matrix<t> operator = (const Matrix<t> &other);
    Matrix<t> operator + (const Matrix<t> &other) const throw(invalid_argument);
    Matrix<t> operator - (const Matrix<t> &other) const throw(invalid_argument);
    Matrix<t> operator * (const Matrix<t> &other) const throw(invalid_argument);
    Matrix<t> operator * (const t &scalar) const;
    const t& operator () (int rowIndex, int columnIndex) const throw(out_of_range);
    t& operator () (int rowIndex, int columnIndex) throw(out_of_range);

    Matrix<t> subMatrix(int excludingRow, int excludingColumn) const throw(logic_error, out_of_range);
    t determinant() const throw(logic_error);
    Matrix<t> transpose () const;

    string toString() const;

private:
    int numRows, numColumns;
    t *data;
};

template <typename t>
Matrix<t>::Matrix(int numRows, int numColumns) : numRows(numRows), numColumns(numColumns), data(new t[numRows * numColumns]) {}

template <typename t>
Matrix<t>::Matrix(int numRows, int numColumns, t *values) : Matrix(numRows, numColumns)
{
    for(int i = 0; i < numRows * numColumns; i++)
        data[i] = values[i];
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
void Matrix<t>::setAllValues(const t &value)
{
    for(int i = 0; i < numRows*numColumns; i++)
        data[i] = value;
}

template <typename t>
void Matrix<t>::setValue(int rowIndex, int columnIndex, const t &value) throw(out_of_range)
{
    if(rowIndex < 0 || rowIndex >= numRows || columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");
    data[columnIndex + rowIndex*numColumns] = value;
}

template <typename t>
t Matrix<t>::getValue(int rowIndex, int columnIndex) const throw(out_of_range)
{
    if(rowIndex < 0 || rowIndex >= numRows || columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");
    return data[columnIndex + rowIndex*numColumns];
}

template <typename t>
void Matrix<t>::pushRow(Matrix<t> row) throw(invalid_argument)
{
    insertRow(numRows, row);
}

template <typename t>
void Matrix<t>::pushColumn(Matrix<t> col) throw(invalid_argument)
{
    insertColumn(numColumns, col);
}

template <typename t>
void Matrix<t>::insertRow(int beforeOfIndex, Matrix<t> rowMat) throw(out_of_range, invalid_argument)
{
    if(beforeOfIndex < 0 || beforeOfIndex > numRows)
        throw out_of_range("Indice non valido");

    if(numColumns != rowMat.numColumns || rowMat.numRows != 1)
        throw invalid_argument("Matrice di dimensioni non valide");

    t* newData = new t[++numRows * numColumns];
    for(int i = 0; i < numRows * numColumns; i++)
    {
        int rowIndex = i/numColumns;
        if(rowIndex < beforeOfIndex)
            newData[i] = data[i];
        else if(rowIndex == beforeOfIndex)
            newData[i] = rowMat(0, i % numColumns);
        else // rowIndex > beforeOfIndex
            newData[i] = data[i - numColumns];
    }
    delete[](data);
    data = newData;
}

template <typename t>
void Matrix<t>::insertColumn(int beforeOfIndex, Matrix<t> colMat) throw(out_of_range, invalid_argument)
{
    if(beforeOfIndex < 0 || beforeOfIndex > numColumns)
        throw out_of_range("Indice non valido");

    if(numRows != colMat.numRows || colMat.numColumns != 1)
        throw invalid_argument("Matrice di dimensioni non valide");

    t* newData = new t[numRows * ++numColumns];
    for(int i = 0; i < numRows * numColumns; i++)
    {
        int rowIndex = i/numColumns;
        int columnIndex = i%numColumns;
        if(columnIndex < beforeOfIndex)
            newData[i] = data[i - rowIndex];
        else if(columnIndex == beforeOfIndex)
            newData[i] = colMat(rowIndex, 0);
        else // columnIndex > beforeOfIndex
            newData[i] = data[i - (rowIndex+1)];
    }
    delete[](data);
    data = newData;
}

template <typename t>
void Matrix<t>::setRow(int rowIndex, Matrix<t> rowMat) throw(out_of_range, invalid_argument)
{
    if(rowIndex < 0 || rowIndex >= numRows)
        throw out_of_range("Indice non valido");

    if(numColumns != rowMat.numColumns || rowMat.numRows != 1)
        throw invalid_argument("Matrice di dimensioni non valide");

    for(int i = 0; i < numColumns; i++)
        (*this)(rowIndex, i) = rowMat(0, i);
}

template <typename t>
void Matrix<t>::setColumn(int columnIndex, Matrix<t> colMat) throw(out_of_range, invalid_argument)
{
    if(columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indice non valido");

    if(numRows != colMat.numRows || colMat.numColumns != 1)
        throw invalid_argument("Matrice di dimensioni non valide");

    for(int i = 0; i < numRows; i++)
        (*this)(i, columnIndex) = colMat(i, 0);
}

template <typename t>
Matrix<t> Matrix<t>::getRow(int rowIndex) const throw(out_of_range)
{
    if(rowIndex < 0 || rowIndex >= numRows)
        throw out_of_range("Indice non valido");

    Matrix<t> output(1, numColumns);
    for(int i = 0; i < numColumns; i++)
        output(0, i) = (*this)(rowIndex, i);

    return output;
}

template <typename t>
Matrix<t> Matrix<t>::getColumn(int columnIndex) const throw(out_of_range)
{
    if(columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indice non valido");

    Matrix<t> output(numRows, 1);
    for(int i = 0; i < numRows; i++)
        output(i, 0) = (*this)(i, columnIndex);

    return output;
}

template <typename t>
void Matrix<t>::removeRow(int rowIndex) throw(out_of_range)
{
    if(rowIndex < 0 || rowIndex >= numRows)
        throw out_of_range("Indice non valido");

    t* newData = new t[--numRows * numColumns];
    for(int i = 0; i < numRows * numColumns; i++)
    {
        if(i/numColumns < rowIndex)
            newData[i] = data[i];
        else
            newData[i] = data[i + numColumns];
    }
    delete[](data);
    data = newData;
}

template <typename t>
void Matrix<t>::removeColumn(int columnIndex) throw(out_of_range)
{
    if(columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indice non valido");

    t* newData = new t[numRows * --numColumns];
    for(int i = 0; i < numRows * numColumns; i++)
    {
        int rowIndex = i/numColumns;
        if(i%(numRows+1) < columnIndex)
            newData[i] = data[i + rowIndex];
        else
            newData[i] = data[i + 1 + rowIndex];
    }
    delete[](data);
    data = newData;
}


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
Matrix<t> Matrix<t>::operator+(const Matrix<t> &other) const throw(invalid_argument)
{
    if(numRows != other.numRows || numColumns != other.numColumns)
        throw invalid_argument("Dimensioni matrici differenti");

    Matrix<t> result(numRows, numColumns);
    for(int i = 0; i < numRows*numColumns; i++)
        result.data[i] =  data[i] + other.data[i];
    return result;
}

template <typename t>
Matrix<t> Matrix<t>::operator-(const Matrix<t> &other) const throw(invalid_argument)
{
    if(numRows != other.numRows || numColumns != other.numColumns)
        throw invalid_argument("Dimensioni matrici differenti");

    Matrix<t> result(numRows, numColumns);
    for(int i = 0; i < numRows*numColumns; i++)
        result.data[i] =  data[i] - other.data[i];
    return result;
}

template <typename t>
Matrix<t> Matrix<t>::operator*(const Matrix<t> &other) const throw(invalid_argument)
{
    if(numColumns != other.numRows)
        throw invalid_argument("Dimensioni non congrue per prodotto");

    Matrix<t> result(numRows, other.numColumns);
    result.setAllValues(0);
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
const t &Matrix<t>::operator () (int rowIndex, int columnIndex) const throw(out_of_range)
{
    if(rowIndex < 0 || rowIndex >= numRows || columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");
    return data[columnIndex + rowIndex*numColumns];
}

template <typename t>
t &Matrix<t>::operator () (int rowIndex, int columnIndex) throw(out_of_range)
{
    if(rowIndex < 0 || rowIndex >= numRows || columnIndex < 0 || columnIndex >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");
    return data[columnIndex + rowIndex*numColumns];
}


template <typename t>
Matrix<t> Matrix<t>::subMatrix(int excludingRow, int excludingColumn) const throw(logic_error, out_of_range)
{
    if(numRows <= 1 || numColumns <= 1)
        throw logic_error("Matrice troppo piccola per estrarre una sottomatrice");

    if(excludingRow < 0 || excludingRow >= numRows || excludingColumn < 0 || excludingColumn >= numColumns)
        throw out_of_range("Indici di riga e/o colonna non validi");

    Matrix<t> result(numRows-1, numColumns-1);

    for(int col = 0; col < numColumns; col++)
    {
        if(col == excludingColumn)
            continue;
        for(int row = 0; row < numRows; row++)
        {
            if(row == excludingRow)
                continue;
            int index = (col > excludingColumn ? col-1 : col) + (row > excludingRow ? row-1 : row)*result.numColumns;
            result.data[index] = data[col + row*numColumns];
        }
    }

    return result;
}


template <typename t>
t Matrix<t>::determinant() const throw(logic_error)
{
    if(numRows != numColumns)
        throw logic_error("Impossibile calcolare il determinante su una matrice non quadrata");

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
string Matrix<t>::toString() const
{
    string toReturn = "Matrix of " + to_string(numRows) + " rows and " + to_string(numColumns) + " columns:\n";
    for(int row = 0; row < numRows; row++)
    {
        toReturn += "\t";
        for(int col = 0; col < numColumns; col++)
            toReturn += " " + to_string(data[col + row*numColumns]);
        toReturn += "\n";
    }
    return toReturn;
}


#endif //MATRICI_MATRIX_H
