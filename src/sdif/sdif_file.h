#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"

#include "mSDIFFile.hpp"

class SDIFFileClass : public BaseObject {
    t_symbol* _fileName = gensym("");
    t_outlet* _out1;

    DataTypeSDIFFile* _sdifFileData;
    DataPtr _dPtr;

    std::vector<DataPtr> _frames;

public:
    SDIFFileClass(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onFloat(float f) override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;

    void m_new(t_symbol* s, const AtomList& l);
    void m_clear(t_symbol* s, const AtomList& l);

    void m_read(t_symbol* s, const AtomList& l);
    void m_write(t_symbol* s, const AtomList& l);

    void m_add_frame(t_symbol* s, const AtomList& l);
    void m_insert_frame(t_symbol* s, const AtomList& l);
    void m_remove_frame(t_symbol* s, const AtomList& l);

    void m_clear_frames(t_symbol* s, const AtomList& l);

    void m_frames(t_symbol* s, const AtomList& l);
    void m_replace_frames(t_symbol* s, const AtomList& l);
};

#endif // SDIF_FILE_H
