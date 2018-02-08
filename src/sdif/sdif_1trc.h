#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"

#include "mSDIFFile.hpp"

class SDIF1TRCClass : public BaseObject {
    t_symbol* _fileName = gensym("");
    t_outlet* _out1;

    DataTypeSDIFFile* _sdifFileData;
    DataPtr _dPtr;

    std::vector<DataPtr> _frames;

public:
    SDIF1TRCClass(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onFloat(float f) override;

    void m_newfile(t_symbol* s, const AtomList& l);
    void m_clear(t_symbol* s, const AtomList& l);

    void m_read(t_symbol* s, const AtomList& l);
    void m_write(t_symbol* s, const AtomList& l);

    void m_add(t_symbol* s, const AtomList& l);
    void m_insert(t_symbol* s, const AtomList& l);
    void m_remove(t_symbol* s, const AtomList& l);

    void m_remove_all_frames(t_symbol* s, const AtomList& l);

    //void m_frames(t_symbol* s, const AtomList& l);
};

#endif // SDIF_FILE_H
