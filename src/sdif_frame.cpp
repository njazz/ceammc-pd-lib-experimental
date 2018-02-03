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

void SDIFFrameClass::onBang()
{
    if (_sdifFrameData->sdifFrame() == 0)
        return;
    dataTo(0, _dPtr);
};

void SDIFFrameClass::onFloat(float f)
{
    if (!_sdifFrameData)
        return;
    if (!_sdifFrameData->sdifFrame())
        return;

    int idx = f;

    if (idx < 0)
        return;
    if (idx >= _sdifFrameData->sdifFrame()->matrixCount())
        return;

    DataPtr p(new DataTypeSDIFMatrix(_sdifFrameData->sdifFrame()->matrices().at(idx)));
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

//void SDIFFrameClass::m_info(t_symbol* s, const AtomList& l)
//{
//    if (!_sdifFrameData->sdifFrame()) {
//        post("sdif.frame: no data");
//        return;
//    }

//    post(_sdifFrameData->sdifFrame()->info().c_str());
//}

void SDIFFrameClass::m_newframe(t_symbol* s, const AtomList& l)
{
    _sdifFrameData = new DataTypeSDIFFrame(new MSDIFFrame());
    _dPtr = DataPtr(_sdifFrameData);
}

void SDIFFrameClass::m_addmatrix(t_symbol* s, const AtomList& l)
{
}
void SDIFFrameClass::m_removematrix(t_symbol* s, const AtomList& l)
{
}

void SDIFFrameClass::m_replace_matrix(t_symbol* s, const AtomList& l)
{
}

void SDIFFrameClass::m_time(t_symbol* s, const AtomList& l)
{
    if (!_sdifFrameData) return;
    if (!_sdifFrameData->sdifFrame()) {
        post("sdif.frame: no data");
        return;
    }

    if (l.size() < 1) {
        AtomList L(gensym("time"));

        L.append(Atom((_sdifFrameData->sdifFrame()->time())));
        L.output(_out1);
    } else {
        float t = l.at(0).asFloat();
        _sdifFrameData->sdifFrame()->setTime(t);
    }
}
void SDIFFrameClass::m_stream_id(t_symbol* s, const AtomList& l)
{
    if (!_sdifFrameData) return;
    if (!_sdifFrameData->sdifFrame()) {
        post("sdif.frame: no data");
        return;
    }

    if (l.size() < 1) {
        AtomList L(gensym("stream_id"));

        L.append(Atom((_sdifFrameData->sdifFrame()->streamID())));
        L.output(_out1);
    } else {
        float i = l.at(0).asFloat();
        _sdifFrameData->sdifFrame()->setStreamID(i);
    }
}

void SDIFFrameClass::m_clear(t_symbol* s, const AtomList& l)
{
    _sdifFrameData = new DataTypeSDIFFrame(0);
    _dPtr = DataPtr(_sdifFrameData);
}

extern "C" {
void setup_sdif0x2eframe()
{
    ObjectFactory<SDIFFrameClass> f("sdif.frame");
//    f.addMethod("info", &SDIFFrameClass::m_info);
    f.addMethod("clear", &SDIFFrameClass::m_clear);
    f.addMethod("new", &SDIFFrameClass::m_newframe);

    f.addMethod("time", &SDIFFrameClass::m_time);
    f.addMethod("stream_id", &SDIFFrameClass::m_stream_id);
}
}

// ==========
