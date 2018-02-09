#include "conv_json.h"

#include "ceammc_dataatom.h"

DataTypeMList* mListFromJSONArray(nlohmann::json j)
{
    DataTypeMList* ret = 0;

    AtomList* mlist = new AtomList();

    for (auto& e : j) {

        if (e.is_array()) {
            DataTypeMList* dl = mListFromJSONArray(e);
            DataAtom* a = new DataAtom(dl);
            mlist->append(a->toAtom());
        }

        else if (e.is_object()) {
            auto ee = e["mlist"];
            if (ee.is_null())
                continue;

            DataTypeMList* dl = mListFromJSONArray(ee);
            DataAtom* a = new DataAtom(dl);
            mlist->append(a->toAtom());
        }

        else if (e.is_number()) {
            float f = e;
            mlist->append(f);
        }

        else if (e.is_string()) {

            std::string str = e;
            mlist->append(Atom(gensym(str.c_str())));
        }
    }

    ret = new DataTypeMList(mlist);
    return ret;
}

DataTypeMList* ConvJSON::toMList(DataTypeJSON* json)
{
    auto l = json->json()["list"];
    if (l.is_null())
        return 0;

    return mListFromJSONArray(l);
}

AtomList* ConvJSON::toList(DataTypeJSON* json)
{

    auto l = json->json()["list"];
    if (l.is_null())
        return 0;

    AtomList* ret = new AtomList();

    for (auto& e : l) {
        if (e.is_number()) {
            float f = e;
            ret->append(f);
        } else {
            std::string str;
            if (e.is_string())
                str = e;
            if (e.is_array())
                str = "<mlist>";
            if (e.is_object())
                str = "<json>";
            ret->append(Atom(gensym(str.c_str())));
        }
    }

    return ret;
}
