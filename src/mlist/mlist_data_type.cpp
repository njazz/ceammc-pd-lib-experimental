#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "ceammc_atomlist.h"
#include "ceammc_dataatom.h"

#include "mlist_data_type.h"

#include "../conv/conv_mlist.h"

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

    AtomList* m = ConvMList::toLlll(const_cast<DataTypeMList*>(this)); //const_cast<DataTypeMList*>(this)->toLlll();

    std::string ret;
    for (int i = 0; i < m->size(); i++) {
        ret += m->at(i).asString();
        if (i < (m->size() - 1))
            ret += " ";
    }

    return ret;
}

// =========

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
