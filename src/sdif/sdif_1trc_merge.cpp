#include "ceammc_factory.h"

#include "ceammc_data.h"

#include "sdif_data_types.h"

#include "sdif_1trc_merge.h"

#include "ceammc_dataatom.h"

#include "math.h"

using namespace ceammc;

SDIF1TRCMergeClass::SDIF1TRCMergeClass(const PdArgs& args)
    : BaseObject(args)
    , _sdifFileData(new DataTypeSDIFFile(0))
    , _dPtr(_sdifFileData)
{
    createInlet();
    _out1 = createOutlet();
}

// ==========

void SDIF1TRCMergeClass::onBang()
{
    if (_sdifFileData->file() == 0)
        return;

    dataTo(0, _dPtr);
};

void SDIF1TRCMergeClass::onFloat(float f)
{
//    if (!_sdifFileData)
//        return;
//    if (!_sdifFileData->file())
//        return;

//    int idx = f;

//    if (idx < 0)
//        return;
//    if (idx >= _sdifFileData->file()->frameCount())
//        return;

//    DataPtr p(new DataTypeSDIFFrame(_sdifFileData->file()->frames().at(idx)));
//    dataTo(0, p);
}

void SDIF1TRCMergeClass::dump() const
{
    OBJ_DBG << "DATA: SDIF FILE";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _sdifFileData->toString();
}

void SDIF1TRCMergeClass::onData(const DataPtr& d)
{
    post("received: %s", d.data()->toString().c_str());
    if (!d.as<DataTypeSDIFFile>())
        return;

    _sdifFileData = const_cast<DataTypeSDIFFile*>(d.as<DataTypeSDIFFile>());
    _dPtr = DataPtr(_sdifFileData);

    if (!_sdifSecondFileData->file())
        return;

    if (!_sdifFileData->file())
        return;

    _sdifFileData->file()->mergeFramesWithSignature("1TRC",_sdifSecondFileData->file());

    onBang();
}

void SDIF1TRCMergeClass::onList(const AtomList& l)
{
    DataAtom a(l.at(0));
    onData(a.data());
}

void SDIF1TRCMergeClass::onInlet(size_t s, const AtomList& l)
{
    DataAtom a(l.at(0));

    if (!a.data().as<DataTypeSDIFFile>())
        return;

    _sdifSecondFileData = const_cast<DataTypeSDIFFile*>(a.data().as<DataTypeSDIFFile>());
}
// ==========

void SDIF1TRCMergeClass::m_newfile(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(new MSDIFFile());
    _dPtr = DataPtr(_sdifFileData);

    _fileName = gensym("<new file>");
    std::string m = "StreamID\t0\nTableName\tSinusoidalTracks\n";
    _sdifFileData->file()->createFrameWithMatix("1NVT", 0, -1, m, m.length());
}

void SDIF1TRCMergeClass::m_clear(t_symbol* s, const AtomList& l)
{
    _sdifFileData = new DataTypeSDIFFile(0);
    _dPtr = DataPtr(_sdifFileData);
}

extern "C" {
void setup_sdif0x2e1trc_merge()
{
    ObjectFactory<SDIF1TRCMergeClass> f("sdif.1trc.merge");

    f.addMethod("new", &SDIF1TRCMergeClass::m_newfile);
    f.addMethod("clear", &SDIF1TRCMergeClass::m_clear);

    //    f.addMethod("read", &SDIF1TRCMergeClass::m_read);
    //    f.addMethod("write", &SDIF1TRCMergeClass::m_write);

    //    f.addMethod("time_scale", &SDIF1TRCMergeClass::m_timescale);
    //    f.addMethod("time_offset", &SDIF1TRCMergeClass::m_timeoffset);
    //    f.addMethod("time_apply", &SDIF1TRCMergeClass::m_timeapply);

    //    f.addMethod("add", &SDIF1TRCMergeClass::m_add);
    //    f.addMethod("insert", &SDIF1TRCMergeClass::m_insert);
    //    f.addMethod("remove", &SDIF1TRCMergeClass::m_remove);

    //    f.addMethod("clear_data", &SDIF1TRCMergeClass::m_remove_all_frames);

    // f.addMethod("list", &SDIF1TRCMergeClass::m_frames);
}
}

// ==========
