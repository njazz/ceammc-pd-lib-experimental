#include "ceammc_data.h"
#include "ceammc_factory.h"

//#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "json_mlist.h"

#include "math.h"

#include "../json/json_data_type.h"
#include "../json/mstring_data_type.h"

using namespace ceammc;

JSONToMList::JSONToMList(const PdArgs& args)
    : BaseObject(args)
    , _mlist(new DataTypeMList(new AtomList()))
    , _dPtr(new DataPtr(_mlist))
{
    //    std::string str = "{}";
    //    _JSON = new DataTypeJSON(str);
    //    _dPtr = new DataPtr(_JSON);
    _out1 = createOutlet();
}

void JSONToMList::onBang()
{
    if (!_mlist)
        return;
    if (!_mlist->list())
        return;
    _mlist->list()->output(_out1);
}

void JSONToMList::onData(const DataPtr& d)
{
    if (!d.as<DataTypeJSON>())
        return;

    post("on data");

    DataTypeJSON* json = const_cast<DataTypeJSON*>(d.as<DataTypeJSON>());

    if (!json) {
        error("bad input json");
        return;
    }

//    post("input %s", json->toString().c_str());

//    auto a = json->json()["mlist"];
//    if (a.is_null()) post("isnull");
//    for (auto e:a)
//    {
//        post("element");
//    }

    _mlist = json->toMList();
    onBang();
}

void JSONToMList::onList(const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {
            onData(DataAtom(l.at(0)).data());
            return;
        }
}

void JSONToMList::dump() const
{
    OBJ_DBG << "DATA: JSON";
    BaseObject::dump();
    //    OBJ_DBG << "id:       " << _dPtr->desc().id;
    //    OBJ_DBG << "refcount: " << _dPtr->refCount();
    //    OBJ_DBG << "contents:  " << _JSON->toString();
}

// ==========

extern "C" {
void setup_conv_json_mlist()
{
    ObjectFactory<JSONToMList> f("conv.json->mlist");
    f.addAlias("json->mlist");
}
}

// ==========
