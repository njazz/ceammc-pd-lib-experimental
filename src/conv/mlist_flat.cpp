#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "ceammc_dataatom.h"

#include "mlist_flat.h"

#include "math.h"

using namespace ceammc;

MListFlat::MListFlat(const PdArgs& args)
    : BaseObject(args)
    , _MList(new DataTypeMList(0))
    , _dPtr(_MList)
{
    _out1 = createOutlet();
}

void MListFlat::onBang()
{
    if (_MList->list() == 0)
        return;

    if (_outputData)
        dataTo(0, _dPtr);
    else
        _MList->list()->output(_out1);
};

void MListFlat::onData(const DataPtr& d)
{
    if (!d.as<DataTypeMList>())
        return;

    _MList = const_cast<DataTypeMList*>(d.as<DataTypeMList>());
    _MList->toFlatList()->output(_out1);
}

void MListFlat::onList(const AtomList& l)
{
    AtomList* out = DataTypeMList(new AtomList(l)).toFlatList();
    out->output(_out1);
}

void MListFlat::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _MList->toString();
}

// ==========

extern "C" {
void setup_mlist0x2eflat()
{
    ObjectFactory<MListFlat> f("conv.mlist->flat");
    f.addAlias("mlist->flat");
}
}

// ==========