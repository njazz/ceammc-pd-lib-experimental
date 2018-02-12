#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "json_recorder.h"

#include "math.h"

#include "mstring_data_type.h"

#include "../conv/conv_json.h"
#include "../conv/conv_list.h"
#include "../conv/conv_mlist.h"

#include <chrono>

using namespace ceammc;

JSONRecorder::JSONRecorder(const PdArgs& args)
    : BaseObject(args)
    , _JSON(new DataTypeJSON("{}"))
    , _dPtr(new DataPtr(_JSON))
{
    _out1 = createOutlet();
}

void JSONRecorder::onBang()
{
    dataTo(0, *_dPtr);
};

void JSONRecorder::onData(const DataPtr& d)
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

void JSONRecorder::onList(const AtomList& l)
{

    if (l.size() < 1)
        return;

    if (!_isRecording)
        return;

    auto duration = std::chrono::steady_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    int key = millis - _startTime;

    DataTypeMList* ml = new DataTypeMList(new AtomList(l));
    //DataTypeJSON* jj = ConvMList::toJSON(ml);

    DataTypeJSON jj("{\"_set\":" + ConvMList::toJSONString(ml) + "}");
    _JSON->set(std::to_string(key), jj.json()["_set"]);
}

void JSONRecorder::dump() const
{
    OBJ_DBG << "DATA: JSON";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _JSON->toString();
}
// ==========

void JSONRecorder::m_set_mlist(t_symbol* s, const AtomList& l)
{
}

void JSONRecorder::m_set_json(t_symbol* s, const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {
            if (DataAtom(l.at(0)).data().data()->type() == DataTypeJSON::dataType) {
                onData(DataAtom(l.at(0)).data());
                return;
            }
        }

    /*
    if (l.size() < 1)
        return;

    if (!_isRecording) return;

    auto duration =  std::chrono::steady_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    float key = millis;

    DataAtom a(l.at(0));
    DataTypeJSON* ml = const_cast<DataTypeJSON*>(a.data().as<DataTypeJSON>());
    if (!ml)
        return;

    _JSON->set(key, ml->json());
    */
}

void JSONRecorder::m_record(t_symbol* s, const AtomList& l)
{
    _isRecording = true;

    auto duration = std::chrono::steady_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    _startTime = millis;
}

void JSONRecorder::m_stop(t_symbol* s, const AtomList& l)
{
    _isRecording = false;
}

void JSONRecorder::m_clear(t_symbol* s, const AtomList& l)
{
    _JSON->clear();
}

// ==========

extern "C" {
void setup_json_recorder()
{
    ObjectFactory<JSONRecorder> f("json.recorder");

    f.addMethod("record", &JSONRecorder::m_record);
    f.addMethod("stop", &JSONRecorder::m_stop);

    f.addMethod("set_json", &JSONRecorder::m_set_json);

    f.addMethod("clear", &JSONRecorder::m_clear);
}
}

// ==========
