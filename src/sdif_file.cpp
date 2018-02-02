#include "ceammc_factory.h"

#include "ceammc_data.h"

#include "sdif_data_types.h"

#include "sdif_file.h"

using namespace ceammc;

SDIFFileClass::SDIFFileClass(const PdArgs& args)
    : BaseObject(args)
    , _sdifFileData(new DataTypeSDIFFile(0))
    , _dPtr(_sdifFileData)
{
    _out1 = createOutlet();
}

void SDIFFileClass::onBang()
{
    if (_sdifFileData->sdifFile() == 0)
        return;
    dataTo(0, _dPtr);
};

void SDIFFileClass::onFloat(float f)
{
    if (!_sdifFileData) return;
    if (!_sdifFileData->sdifFile())
        return;

    int idx = f;

    if (idx < 0)
        return;
    if (idx >= _sdifFileData->sdifFile()->frames.size())
        return;

    DataPtr p(new DataTypeSDIFFrame(_sdifFileData->sdifFile()->frames.at(idx)));
    dataTo(0, p);
}

void SDIFFileClass::dump() const
{
    OBJ_DBG << "DATA: SDIF FILE";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sdifFileData->toString();
}

void SDIFFileClass::m_info(t_symbol* s, const AtomList& l)
{
    if (!_sdifFileData->sdifFile()) {
        post("sdif.file: no file");
        return;
    }

    post(_sdifFileData->sdifFile()->info().c_str());
}

void SDIFFileClass::m_frames(t_symbol* s, const AtomList& l)
{
    if (!_sdifFileData->sdifFile())
        return;
    _frames.clear();

    AtomList L(Atom(gensym("frames")));

    for (auto f : _sdifFileData->sdifFile()->frames) {
        _frames.push_back(DataPtr(new DataTypeSDIFFrame(f)));
        L.append(_frames.back().asAtom());
    }

    L.output(_out1);
}

void SDIFFileClass::m_newfile(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(new MSDIFFile());
    _dPtr = DataPtr(_sdifFileData);

    _fileName = gensym("<new file>");
}

void SDIFFileClass::m_clear(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(0);
    _dPtr = DataPtr(_sdifFileData);
}

void SDIFFileClass::m_read(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(new MSDIFFile());
    _dPtr = DataPtr(_sdifFileData);

    mFileError e = _sdifFileData->sdifFile()->readFile(l.at(0).asString());

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

extern "C" {
void setup_sdif0x2efile()
{
    ObjectFactory<SDIFFileClass> f("sdif.file");
    f.addMethod("info", &SDIFFileClass::m_info);
    f.addMethod("newfile", &SDIFFileClass::m_newfile);
    f.addMethod("clear", &SDIFFileClass::m_clear);
    f.addMethod("read", &SDIFFileClass::m_read);
    f.addMethod("frames", &SDIFFileClass::m_frames);
}
}

// ==========
