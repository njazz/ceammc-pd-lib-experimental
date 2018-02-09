#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "json_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

#include "json.hpp"

#include <iostream>
#include <fstream>
#include <streambuf>

#include "../mlist/mlist_data_type.h"

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

// ==========

void DataTypeJSON::toFile(std::string fileName)
{
    std::ofstream f(fileName);
    f << toString();
    f.close();
}

void DataTypeJSON::fromFile(std::string fileName)
{
    std::ifstream f(fileName);
    std::string s((std::istreambuf_iterator<char>(f)),
                     std::istreambuf_iterator<char>());
    f.close();
    _json = json::parse(s);
}

// ==========

DataTypeMList* DataTypeJSON::toMList()
{
    DataTypeMList* ret = 0;

    return ret;
}

void DataTypeJSON::fromList(AtomList& l)
{
    std::string ns = "{\"list\":[";

    std::string str;
    if (l.at(0).isData()) {
        DataAtom a = DataAtom(l.at(0));
        str = a.data()->toString();
        if (strlen(str.c_str()) == 0)
            str = "0";
        else
            str = "\""+str+"\"";
    } else
        str = l.at(0).asString();

    ns += str;


    for (int i = 1; i < l.size(); i++) {
        std::string str;
        if (l.at(i).isData()) {
            DataAtom a = DataAtom(l.at(i));
            str = a.data()->toString();
            if (strlen(str.c_str()) == 0)
                str = "0";
            else
                str = "\""+str+"\"";
        } else
            str = l.at(i).asString();

        ns += "," + str;
    }
    ns += "]}";

    _json = json::parse(ns);
}

AtomList* DataTypeJSON::toList()
{

    auto l = _json["list"];
    if (l.is_null())
        return 0;

    auto a = _json["list"];

    AtomList* ret = new AtomList();

    for (auto e : a)
    {
        std::string str = a;
        ret->append(Atom(gensym(str.c_str())));
    }

    return ret;
}

