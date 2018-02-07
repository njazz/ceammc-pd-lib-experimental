#ifndef JSON_DATA_TYPES_H
#define JSON_DATA_TYPES_H

#include "ceammc_data.h"
#include "mSDIFFile.hpp"
#include "ceammc_atomlist.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace ceammc;

class DataTypeJSON : public AbstractData {
    json _json = "{}"_json;

public:
    static const DataType dataType = 200;

    explicit DataTypeJSON(std::string jsonString);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    json json() { return _json; }
};

#endif // SDIF_DATA_TYPES_H
