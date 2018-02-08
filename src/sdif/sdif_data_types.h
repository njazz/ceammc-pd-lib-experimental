#ifndef SDIF_DATA_TYPES_H
#define SDIF_DATA_TYPES_H

#include "ceammc_data.h"
#include "ceammc_datatypes.h"
#include "mSDIFFile.hpp"

using namespace ceammc;

static const ::ceammc::DataType DATA_SDIF_FILE = 101;
static const ::ceammc::DataType DATA_SDIF_FRAME = 102;
static const ::ceammc::DataType DATA_SDIF_MATRIX = 103;

class DataTypeSDIFFile : public AbstractData {
    MSDIFFile* _file = 0;

public:
    static const DataType dataType = DATA_SDIF_FILE;

    explicit DataTypeSDIFFile(MSDIFFile* f);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    MSDIFFile* file() { return _file; }
};

// ==========

class DataTypeSDIFFrame : public AbstractData {
    MSDIFFrame* _frame = 0;

public:
    static const DataType dataType = DATA_SDIF_FRAME;

    explicit DataTypeSDIFFrame(MSDIFFrame* f);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    MSDIFFrame* frame() { return _frame; }
};

// ==========

class DataTypeSDIFMatrix : public AbstractData {
    MSDIFMatrix* _matrix = 0;

public:
    static const DataType dataType = DATA_SDIF_MATRIX;

    explicit DataTypeSDIFMatrix(MSDIFMatrix* f);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    MSDIFMatrix* matrix() { return _matrix; }
};

#endif // SDIF_DATA_TYPES_H
