#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "mstring_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

#include "json.hpp"

using json = nlohmann::json;

DataTypeString::DataTypeString(std::string str)
{
    _str = str;
}

void DataTypeString::dump()
{
}

DataType DataTypeString::type() const
{
    return dataType;
}

AbstractData* DataTypeString::clone() const
{
    return new DataTypeString(_str);
}

std::string DataTypeString::toString() const
{
    std::string ret = _str;
    return ret;
}
