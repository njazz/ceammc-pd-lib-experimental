#include "conv_mlist.h"

#include "ceammc_platform.h"

#include "ceammc_log.h"

#include "ceammc_dataatom.h"

DataTypeImage* ConvMList::toImage(DataTypeMList* mlist)
{
    DataTypeImage* ret;

    if (!mlist) {
        LIB_ERR << "first element is not an mlist";
        return 0;
    }

    int w = mlist->minimalSublistLength();
    int h = mlist->list()->size();

    LIB_ERR << "w h" << w << h;

    AtomList* l = mlist->list();

    ret = new DataTypeImage(new CImg<unsigned char>(w, h));

    for (int i = 0; i < h; i++) {
        DataTypeMList* nl = const_cast<DataTypeMList*>(DataAtom(l->at(i)).data().as<DataTypeMList>());
        if (!nl) {
            LIB_ERR << "bad list format";
            return 0;
        }

        AtomList* sL = nl->list();

        if (sL->size() < w) {
            LIB_ERR << "mlist length is less than expected";
            return 0;
        }

        for (int j = 0; j < w; j++) {

            unsigned char c = sL->at(j).asFloat();

            ret->img()->set_linear_atXY(c, j, i);
        }
    }

    return ret;
}
DataTypeJSON* ConvMList::toJSON(DataTypeMList* mlist)
{
    DataTypeJSON* ret;

    return ret;
}

AtomList* ConvMList::toLlll(DataTypeMList* mlist)
{
    AtomList* ret = new AtomList(Atom(gensym("(")));
    AtomList* list = mlist->list();
    //
    for (int i = 0; i < list->size(); i++) {

        if (list->at(i).isData()) {
            DataAtom da = DataAtom(list->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e =  ConvMList::toLlll(s); //s->toLlll();

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(list->at(i));
            }
        } else {
            ret->append(list->at(i));
        }
    }

    //
    ret->append((Atom(gensym(")"))));
    return ret;
}

AtomList* ConvMList::toFlatList( DataTypeMList *mlist)
{
    AtomList* ret = new AtomList();
    AtomList* list = mlist->list();
    //
    for (int i = 0; i < list->size(); i++) {

        if (list->at(i).isData()) {
            DataAtom da = DataAtom(list->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e = ConvMList::toFlatList(s); //s->toFlatList();

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(list->at(i));
            }
        } else {
            ret->append(list->at(i));
        }
    }

    //
    return ret;
}

std::string ConvMList::toJSONString(DataTypeMList* mlist)
{
    AtomList* list = mlist->list();
    std::string ret = "[";
    //
    for (int i = 0; i < list->size(); i++) {

        if (list->at(i).isData()) {
            DataAtom da = DataAtom(list->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                std::string e = ConvMList::toJSONString(s);//s->toJSONString();
                ret += e;

                if (i < (list->size() - 1))
                    ret += ",";

                continue;
            }
        }

        if (list->at(i).isSymbol())
            ret += "\"" + list->at(i).asString() + "\"";
        else
            ret += list->at(i).asString();

        if (i < (list->size() - 1))
            ret += ",";
    }
    //
    ret += "]";
    return ret;
}
