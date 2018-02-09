#include "conv_json.h"

#include "ceammc_dataatom.h"

DataTypeImage* ConvJSON::toImage(DataTypeJSON* json)
{
    DataTypeImage* ret;

    return ret;
}

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

        else if (e.is_object()) {
            auto ee = e["mlist"];
            if (ee.is_null())
                continue;

            DataTypeMList* dl = mListFromJSONArray(ee); //new DataTypeMList(new AtomList(Atom(gensym("mlist"))));
            DataAtom* a = new DataAtom(dl);
            ml->append(a->toAtom());
        }

        else if (e.is_number()) {
            float f = e;
            ml->append(f);
        }

        else if (e.is_string()) {

            std::string str = e;
            ml->append(Atom(gensym(str.c_str())));
        }
    }

    ret = new DataTypeMList(ml);
    return ret;
}

DataTypeMList* ConvJSON::toMList(DataTypeJSON* json)
{

    auto l = json->json()["mlist"];
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
            std::string str = e;
            ret->append(Atom(gensym(str.c_str())));
        }
    }

    return ret;

    return ret;
}
