#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "sublist_data_type.h"

#include "ceammc_atomlist.h"

DataTypeSubList::DataTypeSubList(AtomList* l)
{
    _atomList = l;
}

void DataTypeSubList::dump()
{

}

DataType DataTypeSubList::type() const
{
    return dataType;
}

AbstractData* DataTypeSubList::clone() const
{
    // todo
    return new DataTypeSubList(new AtomList(*_atomList));
}

std::string DataTypeSubList::toString() const
{
    if (!_atomList)
        return "[empty]";

    std::string ret;
    for (int i=0;i<_atomList->size();i++)
        ret += _atomList->at(i).asString()+" ";

    return ret;
}

