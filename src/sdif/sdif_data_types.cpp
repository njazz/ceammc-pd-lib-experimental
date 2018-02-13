#include "sdif_data_types.h"

#include "m_pd.h"

#include "ceammc_datatypes.h"

DataTypeSDIFFile::DataTypeSDIFFile(MSDIFFile* f)
{
    _file = f;
}

void DataTypeSDIFFile::dump()
{
    if (!_file) {
        post("sdif.file: empty");
        return;
    }

    post("sdif.file: frame count: %i", _file->frameCount());
}

DataType DataTypeSDIFFile::type() const
{
    return dataType;
}

AbstractData* DataTypeSDIFFile::clone() const
{
    // todo
    return new DataTypeSDIFFile(_file);
}

std::string DataTypeSDIFFile::toString() const
{
    if (!_file)
        return "[empty file]";
    return _file->info();
}

// ===========

DataTypeSDIFFrame::DataTypeSDIFFrame(MSDIFFrame* f)
{
    _frame = f;
}

void DataTypeSDIFFrame::dump()
{
    if (!_frame) {
        post("sdif.file: empty");
        return;
    }

    post("sdif.frame: matrix count: %i", _frame->matrixCount());
}

DataType DataTypeSDIFFrame::type() const
{
    return dataType;
}

AbstractData* DataTypeSDIFFrame::clone() const
{
    // todo
    return (0);
}

std::string DataTypeSDIFFrame::toString() const
{
    if (!_frame)
        return "[empty file]";
    return _frame->info();
}

// ===========

DataTypeSDIFMatrix::DataTypeSDIFMatrix(MSDIFMatrix* f)
{
    _matrix = f;
}

void DataTypeSDIFMatrix::dump()
{
    if (!_matrix) {
        post("sdif.file: empty");
        return;
    }

    post("sdif.matrix: rows %i columns %i", _matrix->rows(), _matrix->columns());
}

DataType DataTypeSDIFMatrix::type() const
{
    return dataType;
}

AbstractData* DataTypeSDIFMatrix::clone() const
{
    // todo
    return (0);
}

std::string DataTypeSDIFMatrix::toString() const
{
    if (!_matrix)
        return "[empty file]";
    return _matrix->info();
}


