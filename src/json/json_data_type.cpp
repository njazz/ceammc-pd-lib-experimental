#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "json_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

#include "json.hpp"

using json = nlohmann::json;

DataTypeJSON::DataTypeJSON(std::string jsonString)
{
    auto input = json::parse(jsonString);

    if (input.is_null())
        _json = json::parse("{}");
    else
        _json = input;
}

void DataTypeJSON::dump()
{
}

DataType DataTypeJSON::type() const
{
    return dataType;
}

AbstractData* DataTypeJSON::clone() const
{
    // todo
    return new DataTypeJSON(_json.dump());
}

std::string DataTypeJSON::toString() const
{
    std::string ret = _json.dump();
    return ret;
}
