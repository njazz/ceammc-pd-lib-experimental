#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "ceammc_dataatom.h"

#include "mlist_json.h"

#include "math.h"

#include "../mlist/mlist_data_type.h"

#include "../conv/conv_mlist.h"

using namespace ceammc;

MListToJSON::MListToJSON(const PdArgs& args)
    : BaseObject(args)
    , _json(new DataTypeJSON("{}"))
    , _dPtr(new DataPtr(_json))
{
    _out1 = createOutlet();
}

void MListToJSON::onBang()
{
    if (!_dPtr)
        return;

    dataTo(0, *_dPtr);
};

void MListToJSON::onData(const DataPtr& d)
{
    if (!d.as<DataTypeMList>())
        return;

    DataTypeMList* mlist = const_cast<DataTypeMList*>(d.as<DataTypeMList>());
    if (!mlist) {
        error("bad input list");
        return;
    }

    std::string str = "{\"mlist\":" + ConvMList::toJSONString(mlist) + "}";
    try {
        _json = new DataTypeJSON(str);
        _dPtr = new DataPtr(_json);
        onBang();
    } catch (std::exception& e) {
        error("couldn't create json: %s", str.c_str());
    }
}

void MListToJSON::onList(const AtomList& l)
{
    AtomList ll = l;
    DataTypeMList* m = new DataTypeMList(&ll);
    DataPtr p = DataPtr(m);
    onData(p);
}

void MListToJSON::onFloat(float f)
{
    onList(AtomList(Atom(f)));
}

void MListToJSON::onSymbol(t_symbol* s)
{
    onList(AtomList(Atom(s)));
}

void MListToJSON::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _json->toString();
}

// ==========

extern "C" {
void setup_conv_mlist_json()
{
    ObjectFactory<MListToJSON> f("conv.mlist->json");
    f.addAlias("mlist->json");
}
}

// ==========
