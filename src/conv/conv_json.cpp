#include "conv_json.h"

 DataTypeImage* ConvJSON::toImage(DataTypeJSON* json)
{
    DataTypeImage *ret;

    return ret;
}

 DataTypeMList* ConvJSON::toMList(DataTypeJSON* json)
{
    DataTypeMList *ret;

    return ret;
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


