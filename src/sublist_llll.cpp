#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "sublist_data_type.h"

#include "ceammc_dataatom.h"

#include "sublist_llll.h"

#include "math.h"

using namespace ceammc;

SublistLlll::SublistLlll(const PdArgs& args)
    : BaseObject(args)
    , _sublist(new DataTypeSubList(0))
    , _dPtr(_sublist)
{
    _out1 = createOutlet();
}

void SublistLlll::onBang()
{
    if (_sublist->list() == 0)
        return;

    if (_outputData)
        dataTo(0, _dPtr);
    else
        _sublist->list()->output(_out1);
};

AtomList* convertList(AtomList src)
{
    AtomList* ret = new AtomList(Atom(gensym("(")));
    //
    for (int i = 0; i < src.size(); i++) {

        if (src.at(i).isData()) {
            DataAtom da = DataAtom(src.at(i));
            DataTypeSubList* s = const_cast<DataTypeSubList*>(da.data().as<DataTypeSubList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e = convertList(sl);

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(src.at(i));
            }
        } else {
            ret->append(src.at(i));
        }
    }

    //
    ret->append((Atom(gensym(")"))));
    return ret;
}

void SublistLlll::onData(const DataPtr& d)
{
    if (!d.as<DataTypeSubList>())
        return;

    _sublist = const_cast<DataTypeSubList*>(d.as<DataTypeSubList>());

    convertList(AtomList(*_sublist->list()))->output(_out1);
}

void SublistLlll::onList(const AtomList& l)
{
    AtomList* out = convertList(l);
    out->output(_out1);
}

void SublistLlll::dump() const
{
    OBJ_DBG << "DATA: Sublist";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sublist->toString();
}

// ==========

extern "C" {
void setup_sublist0x2ellll()
{
    ObjectFactory<SublistLlll> f("sublist.llll");
}
}

// ==========
