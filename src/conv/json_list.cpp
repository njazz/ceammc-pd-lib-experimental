#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../json/json_data_type.h"

#include "ceammc_dataatom.h"

#include "json_list.h"

#include "math.h"

#include "../json/mstring_data_type.h"

#include "conv_json.h"

using namespace ceammc;

JSONToList::JSONToList(const PdArgs& args)
    : BaseObject(args)

{
    _list = 0;
    _out1 = createOutlet();
}

void JSONToList::onBang()
{
    if (!_list) return;
    _list->output(_out1);
}


void JSONToList::onData(const DataPtr& d)
{
    if (!d.as<DataTypeJSON>())
        return;

    DataTypeJSON* json = const_cast<DataTypeJSON*>(d.as<DataTypeJSON>());
    if (!json)
    {
        error("bad input json");
        return;
    }


    _list = ConvJSON::toList(json);//json->toList();
    onBang();

}

void JSONToList::onList(const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {
            onData(DataAtom(l.at(0)).data());
            return;
        }

}

void JSONToList::dump() const
{
    OBJ_DBG << "DATA: JSON";
    BaseObject::dump();
    //    OBJ_DBG << "id:       " << _dPtr->desc().id;
    //    OBJ_DBG << "refcount: " << _dPtr->refCount();
    //    OBJ_DBG << "contents:  " << _JSON->toString();
}

// ==========

extern "C" {
void setup_conv_json_list()
{
    ObjectFactory<JSONToList> f("conv.json->list");
    f.addAlias("json->list");
}
}

// ==========
