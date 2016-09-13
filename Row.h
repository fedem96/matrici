//
// Created by federico on 02/09/16.
//

#ifndef MATRICI_ROW_H
#define MATRICI_ROW_H

#include <list>

using namespace std;

/**
 * TODO implement math operators in class Row
 */
template <typename t>
class Row
{
public:
    Row(int width);
    Row(int width, t *vals);

    int getWidth();

    void pushValue(t val);
    void insertValue(int beforeOfIndex, t val) throw(out_of_range);

    void setValue(int index, t value) throw(out_of_range);
    const t& getValue(int index) const throw(out_of_range);

    void removeValue(int index) throw(out_of_range);

    bool operator == (const Row &other) const;
    bool operator != (const Row &other) const;
    Row<t> operator + (const Row<t> &other) const throw(invalid_argument);
    Row<t> operator - (const Row<t> &other) const throw(invalid_argument);
    Row<t> operator * (const t &scalar) const;
    
    const t& operator () (int index) const throw(out_of_range);
    t& operator () (int index) throw(out_of_range);

private:
    vector<t> values;
    int width;
};

template <typename t>
Row<t>::Row(int width) : width(width)
{
    values.reserve(static_cast<unsigned long>(width));
}

template <typename t>
Row<t>::Row(int width, t *vals) : Row(width)
{
    for(int i = 0; i < width; i++)
        values.push_back(vals[i]);
}

template <typename t>
int Row<t>::getWidth()
{
    return width;
}

template <typename t>
void Row<t>::pushValue(t val)
{
    values.push_back(val);
    ++width;
}

template <typename t>
void Row<t>::insertValue(int beforeOfIndex, t val) throw(out_of_range)
{
    if(beforeOfIndex < 0 || beforeOfIndex > width)
        throw out_of_range("Indice non valido");
    auto it = values.begin();
    for(int i = 0; i < beforeOfIndex; i++)
        it++;
    values.insert(it, val);
    ++width;
}

template <typename t>
void Row<t>::setValue(int index, t value) throw(out_of_range)
{
    if(index < 0 || index >= width)
        throw out_of_range("Indice non valido");
    values[index] = value;
}

template <typename t>
const t& Row<t>::getValue(int index) const throw(out_of_range)
{
    if(index < 0 || index >= width)
        throw out_of_range("Indice non valido");
    return values[index];
}

template <typename t>
void Row<t>::removeValue(int index) throw(out_of_range)
{
    if(index < 0 || index >= width)
        throw out_of_range("Indice non valido");
    for(int i = index; i < width-1; i++)
        values[i] = values[i+1];
    values.pop_back();
    --width;
}

template <typename t>
bool Row<t>::operator == (const Row<t> &other) const
{
    if(width != other.width)
        return false;
    for(int i = 0; i < width; i++)
        if(getValue(i) != other.getValue(i))
            return false;
    return true;
}

template <typename t>
bool Row<t>::operator != (const Row<t> &other) const
{
    return !(*this == other);
}

template <typename t>
const t &Row<t>::operator()(int index) const throw(out_of_range)
{
    if(index < 0 || index >= width)
        throw out_of_range("Indice non valido");
    return values[index];
}

template <typename t>
t &Row<t>::operator()(int index) throw(out_of_range)
{
    if(index < 0 || index >= width)
        throw out_of_range("Indice non valido");
    return values[index];
}

#endif //MATRICI_ROW_H
