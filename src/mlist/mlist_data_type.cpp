#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

DataTypeMList::DataTypeMList(AtomList* l)
{
    _list = l;
}

void DataTypeMList::dump()
{
}

DataType DataTypeMList::type() const
{
    return dataType;
}

AbstractData* DataTypeMList::clone() const
{
    // todo
    return new DataTypeMList(new AtomList(*_list));
}

// =========

std::string DataTypeMList::toString() const
{
    if (!_list)
        return "[empty]";

    AtomList* m = const_cast<DataTypeMList*>(this)->toLlll();

    std::string ret;
    for (int i = 0; i < m->size(); i++)
        ret += m->at(i).asString() + " ";

    return ret;
}

AtomList* DataTypeMList::toLlll()
{
    AtomList* ret = new AtomList(Atom(gensym("(")));
    //
    for (int i = 0; i < _list->size(); i++) {

        if (_list->at(i).isData()) {
            DataAtom da = DataAtom(_list->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e = s->toLlll();

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(_list->at(i));
            }
        } else {
            ret->append(_list->at(i));
        }
    }

    //
    ret->append((Atom(gensym(")"))));
    return ret;
}

AtomList* DataTypeMList::toFlatList()
{
    AtomList* ret = new AtomList();
    //
    for (int i = 0; i < _list->size(); i++) {

        if (_list->at(i).isData()) {
            DataAtom da = DataAtom(_list->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e = s->toFlatList();

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(_list->at(i));
            }
        } else {
            ret->append(_list->at(i));
        }
    }

    //
    return ret;
}

std::string DataTypeMList::toJSONString()
{
    std::string ret = "{\"mlist\":[";
    //
    for (int i = 0; i < _list->size(); i++) {

        if (_list->at(i).isData()) {
            DataAtom da = DataAtom(_list->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                std::string e = s->toJSONString();
                ret += e;

                if (i < (_list->size() - 1))
                    ret += ",";

                continue;
            }
        }

        if (_list->at(i).isSymbol())
            ret += "\"" + _list->at(i).asString() + "\"";
        else
            ret += _list->at(i).asString();

        if (i < (_list->size() - 1))
            ret += ",";
    }
    //
    ret += "]}";
    return ret;
}
int DataTypeMList::minimalSublistLength()
{
    if (!_list)
        return 0;

    int ret = 0;

    for (int i = 0; i < _list->size(); i++) {
        if (!_list->at(i).isData())
            return 1;

        if (!DataAtom(_list->at(i)).data().as<DataTypeMList>())
            return 1;

        int ls = const_cast<DataTypeMList*>(DataAtom(_list->at(i)).data().as<DataTypeMList>())->list()->size();

        if (!ret)
            ret = ls;
        else
            ret = (ls < ret) ? ls : ret;
    }
    return ret;
}

AtomList* DataTypeMList::flip()
{

    if (!_list)
        return 0;

    int ls = minimalSublistLength();

    AtomList* ret = new AtomList();

    if (ls == 1) {
        for (int i = 0; i < _list->size(); i++) {
            DataTypeMList* ml = new DataTypeMList(new AtomList(_list->at(i)));
            ret->append((new DataAtom(ml))->toAtom());
        }

        return ret;
    }

    AtomList* subLists = new AtomList[ls];

    for (int i = 0; i < _list->size(); i++) {

        DataAtom* d = new DataAtom(_list->at(i));
        if (!d)
            continue;

        const DataTypeMList* ml = d->data().as<DataTypeMList>();
        if (!ml)
            continue;

        AtomList* sub = const_cast<DataTypeMList*>(ml)->list();
        if (!sub)
            continue;

        for (int j = 0; j < ls; j++) {
            subLists[j].append(Atom(sub->at(j)));
        }
    }
    for (int i = 0; i < ls; i++) {
        DataTypeMList* ml = new DataTypeMList(&subLists[i]);
        ret->append((new DataAtom(ml))->toAtom());
    }

    return ret;
}
