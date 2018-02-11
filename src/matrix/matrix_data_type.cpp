#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "ceammc_atomlist.h"
#include "ceammc_dataatom.h"

#include "matrix_data_type.h"

#include "../conv/conv_mlist.h"

DataTypeMatrix::DataTypeMatrix(int columns, int rows)
{
    _columns = columns;
    _rows = rows;
    _data = new float[columns * rows];
}

void DataTypeMatrix::dump()
{
}

DataType DataTypeMatrix::type() const
{
    return dataType;
}

AbstractData* DataTypeMatrix::clone() const
{
    return new DataTypeMatrix(_columns, _rows);
}

const float* DataTypeMatrix::at(int x, int y)
{
    size_t pos = x + _columns * y;
    if (pos >= dataSize())
        return 0;

    return &_data[pos];
}

void DataTypeMatrix::set(int x, int y, float v)
{
    size_t pos = x + _columns * y;
    if (pos >= dataSize())
        return;

    _data[pos] = v;
}

const float* DataTypeMatrix::rowAt(int y)
{
    if (y >= _rows)
        return 0;

    return &_data[y * _columns];
}

std::string DataTypeMatrix::toString() const
{
    return "[Matrix " + std::to_string(_columns) + "x" + std::to_string(_rows) + "]";
}
