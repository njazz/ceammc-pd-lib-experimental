#include "conv_list.h"
#include "conv_mlist.h"

#include "ceammc_dataatom.h"

DataTypeJSON* ConvList::toJSON(AtomList* list)
{
    DataTypeJSON* ret = new DataTypeJSON(toJSONString(list));
    return ret;
}

DataTypeImage* ConvList::toImage(AtomList* list)
{
    DataTypeMList* mlist = new DataTypeMList(list);
    return ConvMList::toImage(mlist);
}

std::string ConvList::toJSONString(AtomList* l)
{
    std::string ret = "{\"list\":[";

    std::string str;

    for (int i = 0; i < l->size(); i++) {
        std::string str;
        if (l->at(i).isData()) {
            DataAtom a = DataAtom(l->at(i));
            str = a.data()->toString();
            if (strlen(str.c_str()) == 0)
                str = "0";
            else
                str = "\"" + str + "\"";
        } else {
            if (l->at(i).isSymbol())
                str = "\"" + l->at(i).asString() + "\"";
            else
                str = l->at(i).asString();
        }

        ret += str;
        if (i < (l->size() - 1))
            ret += ",";
    }
    ret += "]}";

    return ret;
}
