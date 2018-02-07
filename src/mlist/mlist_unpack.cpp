#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "mlist_unpack.h"

#include "math.h"

using namespace ceammc;

MListUnpack::MListUnpack(const PdArgs& args)
    : BaseObject(args)
    , _MList(new DataTypeMList(0))
    , _dPtr(new DataPtr(_MList))
{
    _out1 = createOutlet();
}

void MListUnpack::onBang()
{
    if (_MList->list() == 0)
        return;

    if (_outputData)
        dataTo(0, *_dPtr);
    else
        _MList->list()->output(_out1);
};

void MListUnpack::onData(const DataPtr& d)
{
    if (!d.as<DataTypeMList>())
        return;

    _MList = const_cast<DataTypeMList*>(d.as<DataTypeMList>());
    _dPtr = new DataPtr(_MList);

    _outputData = false;

    _MList->list()->output(_out1);
}

void MListUnpack::onList(const AtomList& l)
{
    //if (l.size() == 1)
        if (l.at(0).isData()) {
            onData(DataAtom(l.at(0)).data());
            return;
        }

//    AtomList* nl = new AtomList(l);
//    _MList = new DataTypeMList(nl);
//    _dPtr = new DataPtr(_MList);

//    _outputData = true;
//    dataTo(0, *_dPtr);
}

void MListUnpack::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _MList->toString();
}

// ==========

extern "C" {
void setup_mlist_unpack()
{
    ObjectFactory<MListUnpack> f("mlist.unpack");
}
}

// ==========
