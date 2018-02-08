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

// ==========

void SDIFMatrixClass::onBang()
{
    if (_sdifMatrixData->matrix() == 0)
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

// ==========

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

void SDIFMatrixClass::m_clear(t_symbol* s, const AtomList& l)
{
    _sdifMatrixData = new DataTypeSDIFMatrix(0);
    _dPtr = DataPtr(_sdifMatrixData);
}

// ==========

void SDIFMatrixClass::m_set_size(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->matrix())
        return;

    _sdifMatrixData->matrix()->newSize(l.at(0).asSizeT(), l.at(1).asSizeT());
}

void SDIFMatrixClass::m_type(t_symbol* s, const AtomList& l)
{
    AtomList L(Atom(gensym("type")));
    L.append(Atom(gensym(_sdifMatrixData->matrix()->signature())));
    L.output(_out1);
}

// ==========

void SDIFMatrixClass::m_rowat(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->matrix())
        return;

    AtomList L;

    if (!_sdifMatrixData->matrix()->is<float>())
        return;

    int idx = l.at(0).asInt();
    if (idx < 0)
        return;
    if (idx >= _sdifMatrixData->matrix()->rows())
        return;

    for (int i = 0; i < _sdifMatrixData->matrix()->columns(); i++) {
        L.append(Atom(_sdifMatrixData->matrix()->rowAt<float>(idx)[i]));
    }

    L.output(_out1);
}

void SDIFMatrixClass::m_columnat(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->matrix())
        return;

    AtomList L;

    if (!_sdifMatrixData->matrix()->is<float>())
        return;

    int idx = l.at(0).asInt();
    if (idx < 0)
        return;
    if (idx >= _sdifMatrixData->matrix()->columns())
        return;

    for (int i = 0; i < _sdifMatrixData->matrix()->rows(); i++) {
        L.append(Atom(_sdifMatrixData->matrix()->columnAt<float>(idx)[i]));
    }

    L.output(_out1);
}

void SDIFMatrixClass::m_get(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->matrix())
        return;

    AtomList L;

    if (_sdifMatrixData->matrix()->is<float>()) {
        for (int i = 0; i < _sdifMatrixData->matrix()->rows() * _sdifMatrixData->matrix()->columns(); i++) {
            L.append(Atom(_sdifMatrixData->matrix()->values<float*>()[i]));
        }
    }

    if (_sdifMatrixData->matrix()->is<char>()) {
        std::string v = _sdifMatrixData->matrix()->values<std::string>();
        post("get %s", v.c_str());
        L.append(Atom(gensym(v.c_str())));
    }

    L.output(_out1);
}

void SDIFMatrixClass::m_set(t_symbol* s, const AtomList& l)
{
    if (!_sdifMatrixData)
        return;
    if (!_sdifMatrixData->matrix())
        return;

    if (_sdifMatrixData->matrix()->is<float>()) {
        float c[l.size()];

        for (int i = 0; i < l.size(); i++)
            c[i] = l.at(i).asFloat();

        uint32_t rows = int(floorf(l.size() / _sdifMatrixData->matrix()->columns()));
        if (!rows)
            return;

        post("resized %i %i", rows, _sdifMatrixData->matrix()->columns());

        _sdifMatrixData->matrix()->newSize(rows, _sdifMatrixData->matrix()->columns());
        _sdifMatrixData->matrix()->setValues<float*>(c);
    }

    if (_sdifMatrixData->matrix()->is<char>()) {
        std::string c;

        for (int i = 0; i < l.size(); i++)
            c = c + " " + l.at(i).asString();

        _sdifMatrixData->matrix()->newSize(c.size(), 1);
        _sdifMatrixData->matrix()->setValues<const char*>((c.c_str()));
    }
}

// =========

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

    _sdifMatrixData->matrix()->newSize(v.size(), 1);
    _sdifMatrixData->matrix()->setValues<const char*>((v.c_str()));
}

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
}
}

// ==========
