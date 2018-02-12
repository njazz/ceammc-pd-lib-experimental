#ifndef SDIF_TRC_MERGE_H
#define SDIF_TRC_MERGE_H

#include "ceammc_object.h"

#include "mSDIFFile.hpp"

class SDIF1TRCMergeClass : public BaseObject {
    t_symbol* _fileName = gensym("");
    t_outlet* _out1;

    DataTypeSDIFFile* _sdifFileData;
    DataTypeSDIFFile* _sdifSecondFileData;
    DataPtr _dPtr;

    std::vector<DataPtr> _frames;

public:
    SDIF1TRCMergeClass(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onFloat(float f) override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;
    virtual void onInlet(size_t, const AtomList&) override;

    void m_newfile(t_symbol* s, const AtomList& l);
    void m_clear(t_symbol* s, const AtomList& l);

//    void m_read(t_symbol* s, const AtomList& l);
//    void m_write(t_symbol* s, const AtomList& l);

//    void m_add(t_symbol* s, const AtomList& l);
//    void m_insert(t_symbol* s, const AtomList& l);
//    void m_remove(t_symbol* s, const AtomList& l);

//    void m_remove_all_frames(t_symbol* s, const AtomList& l);

//    void m_timescale(t_symbol* s, const AtomList& l);
//    void m_timeoffset(t_symbol* s, const AtomList& l);
//    void m_timeapply(t_symbol* s, const AtomList& l);

    //void m_frames(t_symbol* s, const AtomList& l);
};

#endif // SDIF_FILE_H
