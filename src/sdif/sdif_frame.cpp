#include "ceammc_factory.h"

#include "ceammc_data.h"

#include "sdif_data_types.h"

#include "sdif_frame.h"

#include "ceammc_dataatom.h"

using namespace ceammc;

SDIFFrameClass::SDIFFrameClass(const PdArgs& args)
    : BaseObject(args)
    , _sdifFrameData(new DataTypeSDIFFrame(0))
    , _dPtr(_sdifFrameData)
{
    _out1 = createOutlet();
}

// =========

void SDIFFrameClass::onBang()
{
    if (_sdifFrameData->frame() == 0)
        return;
    dataTo(0, _dPtr);
};

void SDIFFrameClass::onFloat(float f)
{
    if (!_sdifFrameData)
        return;
    if (!_sdifFrameData->frame())
        return;

    int idx = f;

    if (idx < 0)
        return;
    if (idx >= _sdifFrameData->frame()->matrixCount())
        return;

    DataPtr p(new DataTypeSDIFMatrix(_sdifFrameData->frame()->matrices().at(idx)));
    dataTo(0, p);
}

void SDIFFrameClass::onData(const DataPtr& d)
{
    post("received: %s", d.data()->toString().c_str());
    if (!d.as<DataTypeSDIFFrame>())
        return;

    _sdifFrameData = const_cast<DataTypeSDIFFrame*>(d.as<DataTypeSDIFFrame>());
    _dPtr = DataPtr(_sdifFrameData);
}

void SDIFFrameClass::onList(const AtomList& l)
{
    DataAtom a(l.at(0));
    onData(a.data());
}

void SDIFFrameClass::dump() const
{
    OBJ_DBG << "DATA: SDIF FRAME";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sdifFrameData->toString();
}

// ===========

void SDIFFrameClass::m_newframe(t_symbol* s, const AtomList& l)
{
    std::string t = "1NVT";
    int str_id = -1;

    if (l.size() > 0)
        t = l.at(0).asString();

    if (l.size() > 1)
        str_id = l.at(1).asInt();

    _sdifFrameData = new DataTypeSDIFFrame(new MSDIFFrame(t, str_id));
    _dPtr = DataPtr(_sdifFrameData);
}

void SDIFFrameClass::m_clear(t_symbol* s, const AtomList& l)
{
    _sdifFrameData = new DataTypeSDIFFrame(0);
    _dPtr = DataPtr(_sdifFrameData);
}

// ===========

void SDIFFrameClass::m_time(t_symbol* s, const AtomList& l)
{
    if (!_sdifFrameData)
        return;
    if (!_sdifFrameData->frame()) {
        post("sdif.frame: no data");
        return;
    }

    if (l.size() < 1) {
        AtomList L(gensym("time"));

        L.append(Atom((_sdifFrameData->frame()->time())));
        L.output(_out1);
    } else {
        float t = l.at(0).asFloat();
        _sdifFrameData->frame()->setTime(t);
    }
}
void SDIFFrameClass::m_stream_id(t_symbol* s, const AtomList& l)
{
    if (!_sdifFrameData)
        return;
    if (!_sdifFrameData->frame()) {
        post("sdif.frame: no data");
        return;
    }

    if (l.size() < 1) {
        AtomList L(gensym("stream_id"));

        L.append(Atom((_sdifFrameData->frame()->streamID())));
        L.output(_out1);
    } else {
        float i = l.at(0).asFloat();
        _sdifFrameData->frame()->setStreamID(i);
    }
}

void SDIFFrameClass::m_type(t_symbol* s, const AtomList& l)
{
    AtomList L(Atom(gensym("type")));
    L.append(Atom(gensym(_sdifFrameData->frame()->signature())));
    L.output(_out1);
}

//

void SDIFFrameClass::m_add_matrix(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    DataAtom a(l.at(0));
    if (!a.isData())
        return;

    if (!_sdifFrameData->frame())
        return;

    DataTypeSDIFMatrix* f = const_cast<DataTypeSDIFMatrix*>(a.data().as<DataTypeSDIFMatrix>());
    _sdifFrameData->frame()->addMatrix(f->matrix());
}

void SDIFFrameClass::m_insert_matrix(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    DataAtom a(l.at(1));
    if (!a.isData())
        return;

    if (!_sdifFrameData->frame())
        return;

    DataTypeSDIFMatrix* f = const_cast<DataTypeSDIFMatrix*>(a.data().as<DataTypeSDIFMatrix>());
    _sdifFrameData->frame()->insertMatrix(l.at(0).asInt(), f->matrix());
}

void SDIFFrameClass::m_remove_matrix(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    if (!_sdifFrameData->frame())
        return;

    _sdifFrameData->frame()->removeMatrixAt(l.at(0).asInt());
}

void SDIFFrameClass::m_clear_matrices(t_symbol* s, const AtomList& l)
{
    if (!_sdifFrameData->frame())
        return;

    _sdifFrameData->frame()->removeAllMatrices();
}

void SDIFFrameClass::m_matrices(t_symbol* s, const AtomList& l)
{
    if (!_sdifFrameData->frame())
        return;

    _sdifFrameData->frame()->removeAllMatrices();

    AtomList L(Atom(gensym("matrices")));

    for (auto f : _sdifFrameData->frame()->matrices()) {
        DataPtr* n = new DataPtr(new DataTypeSDIFMatrix(f));
        L.append(n->asAtom());
    }

    L.output(_out1);

}
void SDIFFrameClass::m_replace_matrices(t_symbol* s, const AtomList& l)
{
    if (!_sdifFrameData->frame())
        return;

    _sdifFrameData->frame()->removeAllMatrices();

    for (int i = 0; i < l.size(); i++) {
        DataAtom a(l.at(i));
        if (!a.isData())
            return;

        DataTypeSDIFMatrix* f = const_cast<DataTypeSDIFMatrix*>(a.data().as<DataTypeSDIFMatrix>());
        _sdifFrameData->frame()->addMatrix(f->matrix());
    }
}

extern "C" {
void setup_sdif0x2eframe()
{
    ObjectFactory<SDIFFrameClass> f("sdif.frame");

    f.addMethod("clear", &SDIFFrameClass::m_clear);
    f.addMethod("new", &SDIFFrameClass::m_newframe);

    f.addMethod("time", &SDIFFrameClass::m_time);
    f.addMethod("stream_id", &SDIFFrameClass::m_stream_id);

    f.addMethod("type", &SDIFFrameClass::m_type);

    f.addMethod("add_matrix", &SDIFFrameClass::m_add_matrix);
    f.addMethod("insert_matrix", &SDIFFrameClass::m_insert_matrix);
    f.addMethod("remove_matrix", &SDIFFrameClass::m_remove_matrix);

    f.addMethod("matrices", &SDIFFrameClass::m_matrices);
    f.addMethod("clear_matrices", &SDIFFrameClass::m_clear_matrices);
}
}

// ==========
