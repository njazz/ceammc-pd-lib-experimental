#ifndef SDIF_DATA_TYPES_H
#define SDIF_DATA_TYPES_H

#include "ceammc_data.h"
#include "mSDIFFile.hpp"

using namespace ceammc;

class DataTypeSDIFFile : public AbstractData {
    MSDIFFile* _sdifFile = 0;

public:
    static const DataType dataType = 101;

    explicit DataTypeSDIFFile(MSDIFFile* f);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    MSDIFFile* sdifFile() { return _sdifFile; }
};

class DataTypeSDIFFrame : public AbstractData {
    MSDIFFrame* _sdifFrame = 0;

public:
    static const DataType dataType = 102;

    explicit DataTypeSDIFFrame(MSDIFFrame* f);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    MSDIFFrame* sdifFrame() { return _sdifFrame; }
};

class DataTypeSDIFMatrix : public AbstractData {
    MSDIFMatrix* _sdifMatrix = 0;

public:
    static const DataType dataType = 103;

    explicit DataTypeSDIFMatrix(MSDIFMatrix* f);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    MSDIFMatrix* sdifMatrix() { return _sdifMatrix; }
};

#endif // SDIF_DATA_TYPES_H
