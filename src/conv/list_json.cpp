#include "ceammc_data.h"
#include "ceammc_factory.h"

//#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "list_json.h"

#include "math.h"

#include "../json/mstring_data_type.h"

#include "../conv/conv_list.h"

using namespace ceammc;

ListToJSON::ListToJSON(const PdArgs& args)
    : BaseObject(args)
    , _json(new DataTypeJSON("{}"))
    , _dPtr(new DataPtr(_json))
{
    _out1 = createOutlet();
}

void ListToJSON::onBang()
{
    if (!_dPtr)
        return;

    dataTo(0, *_dPtr);
};

void ListToJSON::onData(const DataPtr& d)
{
    if (!d.as<DataTypeJSON>())
        return;

    DataTypeJSON* JSON = const_cast<DataTypeJSON*>(d.as<DataTypeJSON>());

    std::string ret = JSON->json().dump();

    DataTypeString* s = new DataTypeString(ret);
    DataPtr* ns = new DataPtr(s);
    DataAtom* a = new DataAtom(*ns);

    AtomList(Atom(gensym(ret.c_str()))).output(_out1);
}

void ListToJSON::onList(const AtomList& l)
{

    try {
        _json = ConvList::toJSON(const_cast<AtomList*>(&l));
        //_json = new DataTypeJSON("{}");
        //_json->fromList(const_cast<AtomList&>(l));
        _dPtr = new DataPtr(_json);
        onBang();
    } catch (std::exception& e) {
        error("couldn't create json: %s", e.what());
    }
}

void ListToJSON::dump() const
{
    OBJ_DBG << "DATA: JSON";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _json->toString();
}

// ==========

extern "C" {
void setup_conv_list_json()
{
    ObjectFactory<ListToJSON> f("conv.list->json");
    f.addAlias("list->json");
}
}

// ==========
