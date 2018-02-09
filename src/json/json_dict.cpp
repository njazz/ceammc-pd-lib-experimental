#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "json_dict.h"

#include "math.h"

#include "mstring_data_type.h"

#include "../conv/conv_mlist.h"
#include "../conv/conv_list.h"
#include "../conv/conv_json.h"

using namespace ceammc;

JSONDict::JSONDict(const PdArgs& args)
    : BaseObject(args)
    , _JSON(new DataTypeJSON("{}"))
    , _dPtr(new DataPtr(_JSON))
{
    _out1 = createOutlet();
}

void JSONDict::onBang()
{
    dataTo(0, *_dPtr);
};

void JSONDict::onData(const DataPtr& d)
{
    if (!d.as<DataTypeJSON>())
        return;

    try {
        DataTypeJSON* JSON = const_cast<DataTypeJSON*>(d.as<DataTypeJSON>());
        _JSON = JSON;
        _dPtr = new DataPtr(_JSON);
    } catch (std::exception& e) {
        error("error: %s", e.what());
    }
    onBang();
}

void JSONDict::onList(const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {
            onData(DataAtom(l.at(0)).data());
            return;
        }
}

void JSONDict::dump() const
{
    OBJ_DBG << "DATA: JSON";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _JSON->toString();
}
// ==========

void JSONDict::m_get_list(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    auto j = _JSON->json()[l.at(0).asString()];
    if (j.is_null())
        return;

    json j2;
    j2["list"] = j;

    DataTypeJSON* jj = new DataTypeJSON(j2.dump());
    if (jj) {
        AtomList* ll = ConvJSON::toList(jj);// jj->toList();
        if (ll)
            ll->output(_out1);
    }
}

void JSONDict::m_get_mlist(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    auto j = _JSON->json()[l.at(0).asString()];
    if (j.is_null())
        return;

    json j2;
    j2["mlist"] = j;

    DataTypeJSON* jj = new DataTypeJSON(j2.dump());
    if (jj) {
        DataTypeMList* ll = jj->toMList();
        if (ll) {
            DataPtr* p = new DataPtr(ll);
            DataAtom* a = new DataAtom(*p);
            AtomList listOut(a->toAtom());
            listOut.output(_out1);
        }
    }
}

void JSONDict::m_get_json(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    auto j = _JSON->json()[l.at(0).asString()];
    if (j.is_null())
        return;

    DataPtr* p = new DataPtr(new DataTypeJSON(j.dump()));
    if (!p)
        return;
    DataAtom* a = new DataAtom(*p);
    if (!a)
        return;
    AtomList listOut(a->toAtom());
    listOut.output(_out1);
}

void JSONDict::m_set_list(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    AtomList l2 = l;
    l2.remove(0);

//    DataTypeJSON jj("{}");
//    jj.fromList(l2);

    DataTypeJSON* jj = ConvList::toJSON(&l2);

    _JSON->set(l.at(0).asString(), jj->json()["list"]);
}

void JSONDict::m_set_mlist(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    DataAtom a(l.at(1));
    DataTypeMList* ml = const_cast<DataTypeMList*>(a.data().as<DataTypeMList>());

    if (!ml)
        return;

    DataTypeJSON jj("{\"_set\":" + ConvMList::toJSONString(ml) + "}");
    _JSON->set(l.at(0).asString(), jj.json()["_set"]);
}

void JSONDict::m_set_json(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    DataAtom a(l.at(1));
    DataTypeJSON* ml = const_cast<DataTypeJSON*>(a.data().as<DataTypeJSON>());
    if (!ml)
        return;

    _JSON->set(l.at(0).asString(), ml->json());
}

// ==========

extern "C" {
void setup_json_dict()
{
    ObjectFactory<JSONDict> f("json.dict");

    f.addMethod("get", &JSONDict::m_get_list);
    f.addMethod("set", &JSONDict::m_set_list);

    f.addMethod("get_mlist", &JSONDict::m_get_mlist);
    f.addMethod("set_mlist", &JSONDict::m_set_mlist);

    f.addMethod("get_json", &JSONDict::m_get_json);
    f.addMethod("set_json", &JSONDict::m_set_json);
}
}

// ==========
