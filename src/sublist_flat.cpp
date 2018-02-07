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
    , _dPtr(_sublist)
{
    _out1 = createOutlet();
}

void SublistObj::onBang()
{
    if (_sublist->list() == 0)
        return;

    if (_outputData)
        dataTo(0, _dPtr);
    else
        _sublist->list()->output(_out1);
};

void SublistObj::onData(const DataPtr& d)
{
    //post("received: %s", d.data()->toString().c_str());

    if (!d.as<DataTypeSubList>())
        return;

    _sublist = const_cast<DataTypeSubList*>(d.as<DataTypeSubList>());
    _dPtr = DataPtr(_sublist);

    _outputData = false;

    _sublist->list()->output(_out1);
}

void SublistObj::onList(const AtomList& l)
{
    _sublist = new DataTypeSubList(new AtomList(l));
    _dPtr = DataPtr(_sublist);

    _outputData = true;
    dataTo(0, _dPtr);
}

void SublistObj::dump() const
{
    OBJ_DBG << "DATA: SDIF Matrix";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sublist->toString();
}

//void SublistObj::m_clear(t_symbol* s, const AtomList& l)
//{
//    _sdifMatrixData = new DataTypeSDIFMatrix(0);
//    _dPtr = DataPtr(_sdifMatrixData);
//}

//void SublistObj::m_set(t_symbol* s, const AtomList& l)
//{
//    if (!_sdifMatrixData)
//        return;
//    if (!_sdifMatrixData->sdifMatrix())
//        return;

//    if (_sdifMatrixData->sdifMatrix()->is<float>()) {
//        float c[l.size()];

//        for (int i = 0; i < l.size(); i++)
//            c[i] = l.at(i).asFloat();

//        uint32_t rows = int(floorf(l.size() / _sdifMatrixData->sdifMatrix()->columns()));
//        if (!rows)
//            return;

//        post("resized %i %i", rows, _sdifMatrixData->sdifMatrix()->columns());

//        _sdifMatrixData->sdifMatrix()->newSize(rows, _sdifMatrixData->sdifMatrix()->columns());
//        _sdifMatrixData->sdifMatrix()->setValues<float*>(c);
//    }

//    if (_sdifMatrixData->sdifMatrix()->is<char>()) {
//        std::string c;

//        for (int i = 0; i < l.size(); i++)
//            c = c + " " + l.at(i).asString();

//        _sdifMatrixData->sdifMatrix()->newSize(c.size(), 1);
//        _sdifMatrixData->sdifMatrix()->setValues<const char*>((c.c_str()));
//    }
//}

// ==========

extern "C" {
void setup_sublist()
{
    ObjectFactory<SublistObj> f("sublist");
}
}

// ==========
