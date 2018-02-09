#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "json_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

#include "json.hpp"

#include <fstream>
#include <iostream>
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

DataTypeMList* mListFromJSONArray(nlohmann::json j)
{

    DataTypeMList* ret = 0;

    AtomList* ml = new AtomList(); //Atom(gensym("test")));

//    json ll = j;

//    if (ll.is_array())
//        ml->append(Atom(gensym("array")));

    for (auto& e : j) {

        if (e.is_array()) {
            DataTypeMList* dl = mListFromJSONArray(e); //new DataTypeMList(new AtomList(Atom(gensym("mlist"))));
            DataAtom* a = new DataAtom(dl);
            ml->append(a->toAtom());
        }

        else if (e.is_object())
        {
            auto ee = e["mlist"];
            if (ee.is_null()) continue;

            DataTypeMList* dl = mListFromJSONArray(ee); //new DataTypeMList(new AtomList(Atom(gensym("mlist"))));
            DataAtom* a = new DataAtom(dl);
            ml->append(a->toAtom());
        }

        else if (e.is_number()) {
            float f = e;
            ml->append(f);
        }

        else if (e.is_string()){

            std::string str = e;
            ml->append(Atom(gensym(str.c_str())));

        }
    }

    ret = new DataTypeMList(ml);
    return ret;
}

DataTypeMList* DataTypeJSON::toMList()
{
    auto l = _json["mlist"];
    if (l.is_null())
        return 0;

    return mListFromJSONArray(l);
}

//void DataTypeJSON::fromList(const AtomList& l)
//{
//    std::string ns = "{\"list\":[";

//    std::string str;

//    for (int i = 0; i < l.size(); i++) {
//        std::string str;
//        if (l.at(i).isData()) {
//            DataAtom a = DataAtom(l.at(i));
//            str = a.data()->toString();
//            if (strlen(str.c_str()) == 0)
//                str = "0";
//            else
//                str = "\"" + str + "\"";
//        } else {
//            if (l.at(i).isSymbol())
//                str = "\"" + l.at(i).asString() + "\"";
//            else
//                str = l.at(i).asString();
//        }

//        ns += str;
//        if (i < (l.size() - 1))
//            ns += ",";
//    }
//    ns += "]}";

//    _json = json::parse(ns);
//}

//AtomList* DataTypeJSON::toList()
//{

//    auto l = _json["list"];
//    if (l.is_null())
//        return 0;

//    AtomList* ret = new AtomList();

//    for (auto& e : l) {
//        if (e.is_number()) {
//            float f = e;
//            ret->append(f);
//        } else {
//            std::string str = e;
//            ret->append(Atom(gensym(str.c_str())));
//        }
//    }

//    return ret;
//}
