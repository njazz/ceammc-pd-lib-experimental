#include "ceammc_factory.h"

#include "ceammc_data.h"

#include "sdif_data_types.h"

#include "sdif_file.h"

#include "ceammc_dataatom.h"

using namespace ceammc;

SDIFFileClass::SDIFFileClass(const PdArgs& args)
    : BaseObject(args)
    , _sdifFileData(new DataTypeSDIFFile(0))
    , _dPtr(_sdifFileData)
{
    _out1 = createOutlet();
}

// ==========

void SDIFFileClass::onBang()
{
    if (_sdifFileData->file() == 0)
        return;
    dataTo(0, _dPtr);
};

void SDIFFileClass::onFloat(float f)
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

void SDIFFileClass::onData(const DataPtr& d)
{
    post("received: %s", d.data()->toString().c_str());
    if (!d.as<DataTypeSDIFFile>())
        return;

    _sdifFileData = const_cast<DataTypeSDIFFile*>(d.as<DataTypeSDIFFile>());
    _dPtr = DataPtr(_sdifFileData);
}

void SDIFFileClass::onList(const AtomList& l)
{
    DataAtom a(l.at(0));
    onData(a.data());
}

void SDIFFileClass::dump() const
{
    OBJ_DBG << "DATA: SDIF FILE";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sdifFileData->toString();
}

// ==========

void SDIFFileClass::m_new(t_symbol* s, const AtomList& l)
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

//

void SDIFFileClass::m_read(t_symbol* s, const AtomList& l)
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

void SDIFFileClass::m_write(t_symbol* s, const AtomList& l)
{
    mFileError e = _sdifFileData->file()->writeFile(l.at(0).asString());
    post("sdif.file: written %s", l.at(0).asString().c_str());
}

//

void SDIFFileClass::m_frames(t_symbol* s, const AtomList& l)
{
    if (!_sdifFileData->file())
        return;
    _frames.clear();

    AtomList L(Atom(gensym("frames")));

    for (auto f : _sdifFileData->file()->frames()) {
        _frames.push_back(DataPtr(new DataTypeSDIFFrame(f)));
        L.append(_frames.back().asAtom());
    }

    L.output(_out1);
}

void SDIFFileClass::m_add_frame(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    DataAtom a(l.at(0));
    if (!a.isData())
        return;

    if (!_sdifFileData->file())
        return;

    DataTypeSDIFFrame* f = const_cast<DataTypeSDIFFrame*>(a.data().as<DataTypeSDIFFrame>());
    _sdifFileData->file()->addFrame(f->frame());
}

void SDIFFileClass::m_insert_frame(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    DataAtom a(l.at(1));
    if (!a.isData())
        return;

    if (!_sdifFileData->file())
        return;

    DataTypeSDIFFrame* f = const_cast<DataTypeSDIFFrame*>(a.data().as<DataTypeSDIFFrame>());
    _sdifFileData->file()->insertFrame(l.at(0).asInt(), f->frame());
}

void SDIFFileClass::m_remove_frame(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    if (!_sdifFileData->file())
        return;

    _sdifFileData->file()->removeFrameAt(l.at(0).asInt());
}

void SDIFFileClass::m_clear_frames(t_symbol* s, const AtomList& l)
{
    if (!_sdifFileData->file())
        return;

    _sdifFileData->file()->removeAllFrames();
}

void SDIFFileClass::m_replace_frames(t_symbol* s, const AtomList& l)
{
    if (l.size() < 1)
        return;

    if (!_sdifFileData->file())
        return;

    _sdifFileData->file()->removeAllFrames();

    for (int i=0;i<l.size();i++)
    {
        DataAtom a(l.at(i));
        if (!a.isData())
            continue;

        DataTypeSDIFFrame* f = const_cast<DataTypeSDIFFrame*>(a.data().as<DataTypeSDIFFrame>());
        _sdifFileData->file()->addFrame(f->frame());
    }
}

extern "C" {
void setup_sdif0x2efile()
{
    ObjectFactory<SDIFFileClass> f("sdif.file");

    f.addMethod("newfile", &SDIFFileClass::m_new);
    f.addMethod("clear", &SDIFFileClass::m_clear);

    f.addMethod("read", &SDIFFileClass::m_read);
    f.addMethod("write", &SDIFFileClass::m_write);

    f.addMethod("add_frame", &SDIFFileClass::m_add_frame);
    f.addMethod("insert_frame", &SDIFFileClass::m_insert_frame);
    f.addMethod("remove_frame", &SDIFFileClass::m_remove_frame);

    f.addMethod("clear_frames", &SDIFFileClass::m_clear_frames);

    f.addMethod("frames", &SDIFFileClass::m_frames);
    f.addMethod("replace_frames", &SDIFFileClass::m_replace_frames);
}
}

// ==========
