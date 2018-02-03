#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "sdif_data_types.h"
#include "sdif_matrix.h"

#include "ceammc_dataatom.h"

using namespace ceammc;

SDIFMatrixClass::SDIFMatrixClass(const PdArgs& args)
    : BaseObject(args)
    , _sdifMatrixData(new DataTypeSDIFMatrix(0))
    , _dPtr(_sdifMatrixData)
{
    _out1 = createOutlet();
}

void SDIFMatrixClass::onBang()
{
    if (_sdifMatrixData->sdifMatrix() == 0)
        return;
    dataTo(0, _dPtr);
};

void SDIFMatrixClass::onData(const DataPtr& d)
{
    post("received: %s", d.data()->toString().c_str());
    if (!d.as<DataTypeSDIFMatrix>())
        return;

    _sdifMatrixData = const_cast<DataTypeSDIFMatrix*>(d.as<DataTypeSDIFMatrix>());
    _dPtr = DataPtr(_sdifMatrixData);
}

void SDIFMatrixClass::onList(const AtomList& l)
{
    DataAtom a(l.at(0));
    onData(a.data());
}

void SDIFMatrixClass::dump() const
{
    OBJ_DBG << "DATA: SDIF Matrix";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sdifMatrixData->toString();
}

//void SDIFMatrixClass::m_info(t_symbol* s, const AtomList& l)
//{
//    if (!_sdifMatrixData->sdifMatrix()) {
//        post("sdif.matrix: no data");
//        return;
//    }

//    post(_sdifMatrixData->sdifMatrix()->info().c_str());
//}

void SDIFMatrixClass::m_newmatrix(t_symbol* s, const AtomList& l)
{
    _sdifMatrixData = new DataTypeSDIFMatrix(new MSDIFMatrix());
    _dPtr = DataPtr(_sdifMatrixData);
}

void SDIFMatrixClass::m_clear(t_symbol* s, const AtomList& l)
{
    _sdifMatrixData = new DataTypeSDIFMatrix(0);
    _dPtr = DataPtr(_sdifMatrixData);
}

void SDIFMatrixClass::m_rowat(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->sdifMatrix())
        return;

    AtomList L;

    if (!_sdifMatrixData->sdifMatrix()->is<float>())
        return;

    int idx = l.at(0).asInt();
    if (idx < 0)
        return;
    if (idx >= _sdifMatrixData->sdifMatrix()->header.rows)
        return;

    for (int i = 0; i < _sdifMatrixData->sdifMatrix()->header.columns; i++) {
        L.append(Atom(_sdifMatrixData->sdifMatrix()->rowAt<float>(idx)[i]));
    }

    L.output(_out1);
}

void SDIFMatrixClass::m_type(t_symbol* s, const AtomList& l)
{
    AtomList L(Atom(gensym("type")));
    L.append(Atom(gensym(_sdifMatrixData->sdifMatrix()->signature())));
    L.output(_out1);
}

void SDIFMatrixClass::m_columnat(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->sdifMatrix())
        return;

    AtomList L;

    if (!_sdifMatrixData->sdifMatrix()->is<float>())
        return;

    int idx = l.at(0).asInt();
    if (idx < 0)
        return;
    if (idx >= _sdifMatrixData->sdifMatrix()->header.columns)
        return;

    for (int i = 0; i < _sdifMatrixData->sdifMatrix()->header.rows; i++) {
        L.append(Atom(_sdifMatrixData->sdifMatrix()->columnAt<float>(idx)[i]));
    }

    L.output(_out1);
}

void SDIFMatrixClass::m_data(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->sdifMatrix())
        return;

    AtomList L;

    if (_sdifMatrixData->sdifMatrix()->is<float>()) {
        for (int i = 0; i < _sdifMatrixData->sdifMatrix()->header.rows * _sdifMatrixData->sdifMatrix()->header.columns; i++) {
            L.append(Atom(_sdifMatrixData->sdifMatrix()->values<float>()[i]));
        }
    }

    if (_sdifMatrixData->sdifMatrix()->is<char>()) {
        std::string v = _sdifMatrixData->sdifMatrix()->values<char>();
        L.append(Atom(gensym(v.c_str())));
    }

    L.output(_out1);
}

extern "C" {
void setup_sdif0x2ematrix()
{
    ObjectFactory<SDIFMatrixClass> f("sdif.matrix");
    //    f.addMethod("info", &SDIFMatrixClass::m_info);
    f.addMethod("clear", &SDIFMatrixClass::m_clear);
    f.addMethod("new", &SDIFMatrixClass::m_newmatrix);

    f.addMethod("type", &SDIFMatrixClass::m_type);

    f.addMethod("row_at", &SDIFMatrixClass::m_rowat);
    f.addMethod("column_at", &SDIFMatrixClass::m_columnat);
    f.addMethod("data", &SDIFMatrixClass::m_data);
}
}

// ==========
