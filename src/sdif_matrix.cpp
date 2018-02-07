#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "sdif_data_types.h"
#include "sdif_matrix.h"

#include "ceammc_dataatom.h"

#include "math.h"

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
    std::string t = "1TRC";
    int rows = 0;
    int cols = 0;
    int b = mTFloat4;

    if (l.size() > 0)
        t = l.at(0).asString();

    if (l.size() > 1)
        rows = l.at(1).asSizeT();

    if (l.size() > 2)
        cols = l.at(2).asSizeT();

    _sdifMatrixData = new DataTypeSDIFMatrix(new MSDIFMatrix(t, rows, cols, b));
    _dPtr = DataPtr(_sdifMatrixData);
}

void SDIFMatrixClass::m_set_size(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->sdifMatrix())
        return;

    _sdifMatrixData->sdifMatrix()->newSize(l.at(0).asSizeT(), l.at(1).asSizeT());
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
    if (idx >= _sdifMatrixData->sdifMatrix()->rows())
        return;

    for (int i = 0; i < _sdifMatrixData->sdifMatrix()->columns(); i++) {
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
    if (idx >= _sdifMatrixData->sdifMatrix()->columns())
        return;

    for (int i = 0; i < _sdifMatrixData->sdifMatrix()->rows(); i++) {
        L.append(Atom(_sdifMatrixData->sdifMatrix()->columnAt<float>(idx)[i]));
    }

    L.output(_out1);
}

void SDIFMatrixClass::m_get(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->sdifMatrix())
        return;

    AtomList L;

    if (_sdifMatrixData->sdifMatrix()->is<float>()) {
        for (int i = 0; i < _sdifMatrixData->sdifMatrix()->rows() * _sdifMatrixData->sdifMatrix()->columns(); i++) {
            L.append(Atom(_sdifMatrixData->sdifMatrix()->values<float*>()[i]));
        }
    }

    if (_sdifMatrixData->sdifMatrix()->is<char>()) {
        std::string v = _sdifMatrixData->sdifMatrix()->values<std::string>();
        post("get %s", v.c_str());
        L.append(Atom(gensym(v.c_str())));
    }

    L.output(_out1);
}

void SDIFMatrixClass::m_set(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->sdifMatrix())
        return;

    if (_sdifMatrixData->sdifMatrix()->is<float>()) {
        float c[l.size()];

        for (int i = 0; i < l.size(); i++)
            c[i] = l.at(i).asFloat();

        uint32_t rows = int(floorf(l.size() / _sdifMatrixData->sdifMatrix()->columns()));
        if (!rows)
            return;

        post("resized %i %i", rows, _sdifMatrixData->sdifMatrix()->columns());

        _sdifMatrixData->sdifMatrix()->newSize(rows, _sdifMatrixData->sdifMatrix()->columns());
        _sdifMatrixData->sdifMatrix()->setValues<float*>(c);
    }

    if (_sdifMatrixData->sdifMatrix()->is<char>()) {
        std::string c;

        for (int i = 0; i < l.size(); i++)
            c = c + " " + l.at(i).asString();

        _sdifMatrixData->sdifMatrix()->newSize(c.size(), 1);
        _sdifMatrixData->sdifMatrix()->setValues<const char*>((c.c_str()));
    }
}

void SDIFMatrixClass::m_1nvt(t_symbol* s, const AtomList& l)
{
    if (!l.size())
        return;

    _sdifMatrixData = new DataTypeSDIFMatrix(new MSDIFMatrix("1NVT", 1, 1, mTChar));
    _dPtr = DataPtr(_sdifMatrixData);

    std::string v;

    for (int i = 0; i < int(floorf(l.size() / 2)); i++) {
        v += l.at(i * 2).asString() + "\t" + l.at(i * 2 + 1).asString() + "\n";
    }

    _sdifMatrixData->sdifMatrix()->newSize(v.size(), 1);
    _sdifMatrixData->sdifMatrix()->setValues<const char*>((v.c_str()));

}

//void SDIFMatrixClass::m_1typ(t_symbol* s, const AtomList& l)
//{
//    if (!_sdifMatrixData)
//        return;
//    if (!_sdifMatrixData->sdifMatrix())
//        return;

//    _sdifMatrixData = new DataTypeSDIFMatrix(new MSDIFMatrix("1TYP", 1, 1, mTChar));
//    _dPtr = DataPtr(_sdifMatrixData);

//}

// ==========

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

    f.addMethod("get", &SDIFMatrixClass::m_get);
    f.addMethod("set", &SDIFMatrixClass::m_set);

    f.addMethod("1nvt", &SDIFMatrixClass::m_1nvt);
    f.addMethod("1NVT", &SDIFMatrixClass::m_1nvt);

    //f.addMethod("1typ", &SDIFMatrixClass::m_1typ);
}
}

// ==========
