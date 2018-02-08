#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "mlist_obj.h"

#include "math.h"

using namespace ceammc;

MListObj::MListObj(const PdArgs& args)
    : BaseObject(args)
    , _MList(new DataTypeMList(0))
    , _dPtr(new DataPtr(_MList))
{
    _out1 = createOutlet();
}

void MListObj::onBang()
{
    if (_MList->list() == 0)
        return;

    if (_outputData)
        dataTo(0, *_dPtr);
    else
        _MList->list()->output(_out1);
};


void MListObj::onList(const AtomList& l)
{

    AtomList* nl = new AtomList(l);
    _MList = new DataTypeMList(nl);
    _dPtr = new DataPtr(_MList);

    _outputData = true;
    dataTo(0, *_dPtr);
}

void MListObj::onFloat(float f)
{
    onList(AtomList(Atom(f)));
}

void MListObj::onSymbol(t_symbol* s)
{
    onList(AtomList(Atom(s)));
}

void MListObj::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _MList->toString();
}

// ==========

extern "C" {
void setup_mlist()
{
    ObjectFactory<MListObj> f("mlist");
}
}

// ==========
