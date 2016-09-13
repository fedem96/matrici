//
// Created by federico on 02/09/16.
//

#ifndef MATRICI_COLUMN_H
#define MATRICI_COLUMN_H

#include <list>

using namespace std;

/**
 * TODO implement math operators in class Column
 */
template <typename t>
class Column
{
public:
    Column(int height);
    Column(int height, t *vals);

    int getHeight();

    void pushValue(t val);
    void insertValue(int beforeOfIndex, t val) throw(out_of_range);

    void setValue(int index, t value) throw(out_of_range);
    const t& getValue(int index) const throw(out_of_range);

    void removeValue(int index) throw(out_of_range);

    bool operator == (const Column &other) const;
    bool operator != (const Column &other) const;
    Column<t> operator + (const Column<t> &other) const throw(invalid_argument);
    Column<t> operator - (const Column<t> &other) const throw(invalid_argument);
    Column<t> operator * (const t &scalar) const;

    const t& operator () (int index) const throw(out_of_range);
    t& operator () (int index) throw(out_of_range);

private:
    vector<t> values;
    int height;
};

template <typename t>
Column<t>::Column(int height) : height(height)
{
    values.reserve(static_cast<unsigned long>(height));
}

template <typename t>
Column<t>::Column(int height, t *vals) : Column(height)
{
    for(int i = 0; i < height; i++)
        values.push_back(vals[i]);
}

template <typename t>
int Column<t>::getHeight()
{
    return height;
}

template <typename t>
void Column<t>::pushValue(t val)
{
    values.push_back(val);
    ++height;
}

template <typename t>
void Column<t>::insertValue(int beforeOfIndex, t val) throw(out_of_range)
{
    if(beforeOfIndex < 0 || beforeOfIndex > height)
        throw out_of_range("Indice non valido");
    auto it = values.begin();
    for(int i = 0; i < beforeOfIndex; i++)
        it++;
    values.insert(it, val);
    ++height;
}

template <typename t>
void Column<t>::setValue(int index, t value) throw(out_of_range)
{
    if(index < 0 || index >= height)
        throw out_of_range("Indice non valido");
    values[index] = value;
}

template <typename t>
const t& Column<t>::getValue(int index) const throw(out_of_range)
{
    if(index < 0 || index >= height)
        throw out_of_range("Indice non valido");
    return values[index];
}

template <typename t>
void Column<t>::removeValue(int index) throw(out_of_range)
{
    if(index < 0 || index >= height)
        throw out_of_range("Indice non valido");
    for(int i = index; i < height-1; i++)
        values[i] = values[i+1];
    values.pop_back();
    --height;
}

template <typename t>
bool Column<t>::operator == (const Column<t> &other) const
{
    if(height != other.height)
        return false;
    for(int i = 0; i < height; i++)
        if(getValue(i) != other.getValue(i))
            return false;
    return true;
}

template <typename t>
bool Column<t>::operator != (const Column<t> &other) const
{
    return !(*this == other);
}

template <typename t>
const t &Column<t>::operator()(int index) const throw(out_of_range)
{
    if(index < 0 || index >= height)
        throw out_of_range("Indice non valido");
    return values[index];
}

template <typename t>
t &Column<t>::operator()(int index) throw(out_of_range)
{
    if(index < 0 || index >= height)
        throw out_of_range("Indice non valido");
    return values[index];
}

#endif //MATRICI_COLUMN_H
