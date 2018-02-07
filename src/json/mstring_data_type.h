#ifndef String_DATA_TYPES_H
#define String_DATA_TYPES_H

#include "ceammc_data.h"
#include "mSDIFFile.hpp"
#include "ceammc_atomlist.h"

#include "ceammc_datatypes.h"

using namespace ceammc;

class DataTypeString : public AbstractData {
    std::string _str = "";

public:
    static const DataType dataType = ceammc::data::DATA_STRING;

    explicit DataTypeString(std::string str);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;


};

#endif // SDIF_DATA_TYPES_H
