#include "ceammc_factory.h"

#include "ceammc_data.h"

#include "sdif_data_types.h"

#include "sdif_1trc.h"

#include "ceammc_dataatom.h"

#include "math.h"

using namespace ceammc;

SDIF1TRCClass::SDIF1TRCClass(const PdArgs& args)
    : BaseObject(args)
    , _sdifFileData(new DataTypeSDIFFile(0))
    , _dPtr(_sdifFileData)
{
    _out1 = createOutlet();
}

// ==========

void SDIF1TRCClass::onBang()
{
    if (_sdifFileData->file() == 0)
        return;
    dataTo(0, _dPtr);
};

void SDIF1TRCClass::onFloat(float f)
{
    if (!_sdifFileData)
        return;
    if (!_sdifFileData->file())
        return;

    int idx = f;

    if (idx < 0)
        return;
    if (idx >= _sdifFileData->file()->frameCount())
        return;

    DataPtr p(new DataTypeSDIFFrame(_sdifFileData->file()->frames().at(idx)));
    dataTo(0, p);
}

void SDIF1TRCClass::dump() const
{
    OBJ_DBG << "DATA: SDIF FILE";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sdifFileData->toString();
}

// ==========

//void SDIF1TRCClass::m_frames(t_symbol* s, const AtomList& l)
//{
//    if (!_sdifFileData->sdifFile())
//        return;
//    _frames.clear();

//    AtomList L(Atom(gensym("frames")));

//    for (auto f : _sdifFileData->sdifFile()->frames()) {
//        _frames.push_back(DataPtr(new DataTypeSDIFFrame(f)));
//        L.append(_frames.back().asAtom());
//    }

//    L.output(_out1);
//}

void SDIF1TRCClass::m_newfile(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(new MSDIFFile());
    _dPtr = DataPtr(_sdifFileData);

    _fileName = gensym("<new file>");
    std::string m = "StreamID\t0\nTableName\tSinusoidalTracks\n";
    _sdifFileData->file()->createFrameWithMatix("1NVT", 0, -1, m, m.length());
}

void SDIF1TRCClass::m_clear(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(0);
    _dPtr = DataPtr(_sdifFileData);
}

void SDIF1TRCClass::m_read(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(new MSDIFFile());
    _dPtr = DataPtr(_sdifFileData);

    mFileError e = _sdifFileData->file()->readFile(l.at(0).asString());

    if (e == meOK) {
        _fileName = l.at(0).asSymbol();
        post("sdif.file: loaded %s", _fileName->s_name);
    } else {
        error("sdif.file: could'n load file %s (%i)", l.at(0).asSymbol()->s_name, (int)e);

        _sdifFileData = new DataTypeSDIFFile(0);
        _dPtr = DataPtr(_sdifFileData);

        _fileName = gensym("");
    }
    return;
}

void SDIF1TRCClass::m_write(t_symbol* s, const AtomList& l)
{
    mFileError e = _sdifFileData->file()->writeFile(l.at(0).asString());
    post("sdif.file: written %s", l.at(0).asString().c_str());
}

// =====

void SDIF1TRCClass::m_add(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    if (!_sdifFileData->file())
        return;

    float* ff = new float[l.size() - 1];

    for (int i = 1; i < l.size(); i++) {
        ff[i - 1] = l.at(i).asFloat();
    }

    _sdifFileData->file()->createFrameWithMatix("1TRC", 0, l.at(0).asFloat(), ff, int(floorf(l.size() / 4)));
}

void SDIF1TRCClass::m_insert(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    if (!_sdifFileData->file())
        return;

    float* ff = new float[l.size() - 1];

    for (int i = 2; i < l.size(); i++) {
        ff[i - 2] = l.at(i).asFloat();
    }

    _sdifFileData->file()->insertFrameWithMatix(l.at(0).asInt(), "1TRC", 0, l.at(1).asFloat(), ff, int(floorf(l.size() / 4)));
}

void SDIF1TRCClass::m_remove(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    if (!_sdifFileData->file())
        return;

    _sdifFileData->file()->removeFrameAt(l.at(0).asInt());
}

void SDIF1TRCClass::m_remove_all_frames(t_symbol* s, const AtomList& l)
{
    if (!_sdifFileData->file())
        return;

    _sdifFileData->file()->removeAllFrames();
}

extern "C" {
void setup_sdif0x2e1trc()
{
    ObjectFactory<SDIF1TRCClass> f("sdif.1trc");

    f.addMethod("new", &SDIF1TRCClass::m_newfile);
    f.addMethod("clear", &SDIF1TRCClass::m_clear);

    f.addMethod("read", &SDIF1TRCClass::m_read);
    f.addMethod("write", &SDIF1TRCClass::m_write);

    f.addMethod("add", &SDIF1TRCClass::m_add);
    f.addMethod("insert", &SDIF1TRCClass::m_insert);
    f.addMethod("remove", &SDIF1TRCClass::m_remove);

    f.addMethod("clear_data", &SDIF1TRCClass::m_remove_all_frames);

    // f.addMethod("list", &SDIF1TRCClass::m_frames);
}
}

// ==========
