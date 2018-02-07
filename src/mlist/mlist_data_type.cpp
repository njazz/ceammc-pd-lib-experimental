#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

DataTypeMList::DataTypeMList(AtomList* l)
{
    _atomList = l;
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
    return new DataTypeMList(new AtomList(*_atomList));
}

std::string DataTypeMList::toString() const
{
    if (!_atomList)
        return "[empty]";

    AtomList* m = const_cast<DataTypeMList*>(this)->toLlll();

    std::string ret;
    for (int i=0;i<m->size();i++)
        ret += m->at(i).asString()+" ";

    return ret;
}


AtomList* DataTypeMList::toLlll()
{
    AtomList* ret = new AtomList(Atom(gensym("(")));
    //
    for (int i = 0; i < _atomList->size(); i++) {

        if (_atomList->at(i).isData()) {
            DataAtom da = DataAtom(_atomList->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e = s->toLlll();

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(_atomList->at(i));
            }
        } else {
            ret->append(_atomList->at(i));
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
    for (int i = 0; i < _atomList->size(); i++) {

        if (_atomList->at(i).isData()) {
            DataAtom da = DataAtom(_atomList->at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e = s->toFlatList();

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(_atomList->at(i));
            }
        } else {
            ret->append(_atomList->at(i));
        }
    }

    //
    return ret;
}
