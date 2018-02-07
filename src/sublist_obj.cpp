#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "sublist_data_type.h"

#include "ceammc_dataatom.h"

#include "sublist_obj.h"

#include "math.h"

using namespace ceammc;

SublistObj::SublistObj(const PdArgs& args)
    : BaseObject(args)
    , _sublist(new DataTypeSubList(0))
    , _dPtr(new DataPtr(_sublist))
{
    _out1 = createOutlet();
}

void SublistObj::onBang()
{
    if (_sublist->list() == 0)
        return;

    if (_outputData)
        dataTo(0, *_dPtr);
    else
        _sublist->list()->output(_out1);
};

void SublistObj::onData(const DataPtr& d)
{
    if (!d.as<DataTypeSubList>())
        return;

    _sublist = const_cast<DataTypeSubList*>(d.as<DataTypeSubList>());
    _dPtr = new DataPtr(_sublist);

    _outputData = false;

    _sublist->list()->output(_out1);
}

void SublistObj::onList(const AtomList& l)
{
    AtomList* nl = new AtomList(l);
    _sublist = new DataTypeSubList(nl);
    _dPtr = new DataPtr(_sublist);

    _outputData = true;
    dataTo(0, *_dPtr);

}

void SublistObj::dump() const
{
    OBJ_DBG << "DATA: Sublist";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _sublist->toString();
}


// ==========

extern "C" {
void setup_sublist()
{
    ObjectFactory<SublistObj> f("sublist");
}
}

// ==========
