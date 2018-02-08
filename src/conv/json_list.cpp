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
    //    std::string str = "{}";
    //    _JSON = new DataTypeJSON(str);
    //    _dPtr = new DataPtr(_JSON);
    _out1 = createOutlet();
}

//void JSONObj::onBang()
//{

//    if (_outputData)
//        dataTo(0, *_dPtr);
//    else
////        _JSON->list()->output(_out1);
//};

void JSONObj::onData(const DataPtr& d)
{
    if (!d.as<DataTypeJSON>())
        return;

    DataTypeJSON* JSON = const_cast<DataTypeJSON*>(d.as<DataTypeJSON>());
    //_dPtr = new DataPtr(_JSON);

    //    _outputData = false;

    std::string ret = JSON->json().dump();

    DataTypeString* s = new DataTypeString(ret);
    DataPtr* ns = new DataPtr(s);
    DataAtom* a = new DataAtom(*ns);

    AtomList(Atom(gensym(ret.c_str()))).output(_out1);

    //post("data: %s", ns->data()->toString().c_str());
}

void JSONObj::onList(const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {
            onData(DataAtom(l.at(0)).data());
            return;
        }

    //    AtomList* nl = new AtomList(l);

    std::string ns = "{\"list\":[";

    std::string str;
    if (l.at(0).isData()) {
        DataAtom a = DataAtom(l.at(0));
        str = a.data()->toString();
        if (strlen(str.c_str()) == 0)
            str = "0";
        else
            str = "\""+str+"\"";
    } else
        str = l.at(0).asString();

    ns += str;


    for (int i = 1; i < l.size(); i++) {
        std::string str;
        if (l.at(i).isData()) {
            DataAtom a = DataAtom(l.at(i));
            str = a.data()->toString();
            if (strlen(str.c_str()) == 0)
                str = "0";
            else
                str = "\""+str+"\"";
        } else
            str = l.at(i).asString();

        ns += "," + str;
    }
    ns += "]}";


    post ("%s",ns.c_str());

    //return;

    //todo: try-catch
    try{
    _JSON = new DataTypeJSON(ns);
    _dPtr = new DataPtr(_JSON);
    dataTo(0, *_dPtr);
    }
    catch(const std::exception& e){
       error ("JSON error: could not create %s",ns.c_str());
    }
}

void JSONObj::dump() const
{
    OBJ_DBG << "DATA: JSON";
    BaseObject::dump();
    //    OBJ_DBG << "id:       " << _dPtr->desc().id;
    //    OBJ_DBG << "refcount: " << _dPtr->refCount();
    //    OBJ_DBG << "contents:  " << _JSON->toString();
}

// ==========

extern "C" {
void setup_json()
{
    ObjectFactory<JSONObj> f("json");
}
}

// ==========
