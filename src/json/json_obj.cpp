#include "ceammc_data.h"
#include "ceammc_factory.h"

//#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "json_obj.h"

#include "math.h"

#include "mstring_data_type.h"

using namespace ceammc;

JSONObj::JSONObj(const PdArgs& args)
    : BaseObject(args)
    , _JSON(new DataTypeJSON("{}"))
    , _dPtr(new DataPtr(_JSON))
{
    _out1 = createOutlet();
}

void JSONObj::onBang()
{
    dataTo(0, *_dPtr);
};

void JSONObj::onData(const DataPtr& d)
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

void JSONObj::onList(const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {
            onData(DataAtom(l.at(0)).data());
            return;
        }
}

void JSONObj::dump() const
{
    OBJ_DBG << "DATA: JSON";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _JSON->toString();
}
// ==========
void JSONObj::m_read(t_symbol* s, const AtomList& l)
{
    if (l.size()<1) return;

    try{
    _JSON->fromFile(l.at(0).asString());
    }
    catch(std::exception&e)
    {
        error("couldn't read file");
    }

}
void JSONObj::m_write(t_symbol* s, const AtomList& l)
{
    if (l.size()<1) return;

    try{
    _JSON->toFile(l.at(0).asString());
}
catch(std::exception&e)
{
    error("couldn't write file");
}
}

// ==========

extern "C" {
void setup_json()
{
    ObjectFactory<JSONObj> f("json");

    f.addMethod("read",&JSONObj::m_read);
    f.addMethod("write",&JSONObj::m_write);
}
}

// ==========
