#include "sdif_data_types.h"

#include "m_pd.h"

#include "ceammc_datatypes.h"

DataTypeSDIFFile::DataTypeSDIFFile(MSDIFFile* f)
{
    _sdifFile = f;
}

void DataTypeSDIFFile::dump()
{
    if (!_sdifFile)
    {
        post("sdif.file: empty");
        return;
    }

    post("sdif.file: frame count: %i", _sdifFile->frames.size());
}

DataType DataTypeSDIFFile::type() const
{
    return dataType;
}

AbstractData* DataTypeSDIFFile::clone() const
{
    // todo
    return new DataTypeSDIFFile(_sdifFile);
}

std::string DataTypeSDIFFile::toString() const
{
    if (!_sdifFile) return "[empty file]";
    return _sdifFile->info();
}

// ===========

DataTypeSDIFFrame::DataTypeSDIFFrame(MSDIFFrame* f)
{
    _sdifFrame = f;
}

void DataTypeSDIFFrame::dump()
{
    if (!_sdifFrame)
    {
        post("sdif.file: empty");
        return;
    }

    post("sdif.frame: matrix count: %i", _sdifFrame->matrixCount());
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
    if (!_sdifFrame) return "[empty file]";
    return _sdifFrame->info();
}

// ===========

DataTypeSDIFMatrix::DataTypeSDIFMatrix(MSDIFMatrix* f)
{
    _sdifMatrix = f;
}

void DataTypeSDIFMatrix::dump()
{
    if (!_sdifMatrix)
    {
        post("sdif.file: empty");
        return;
    }

    post("sdif.matrix: rows %i columns %i", _sdifMatrix->header.rows, _sdifMatrix->header.columns);
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
    if (!_sdifMatrix) return "[empty file]";
    return _sdifMatrix->info();
}
