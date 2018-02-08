#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"

#include "mSDIFFile.hpp"

class SDIFFileClass : public BaseObject {
    t_symbol* _fileName = gensym("");
    t_outlet* _out1;

    DataTypeSDIFFile* _sdifFileData;
    DataPtr _dPtr;

public:
    SDIFFileClass(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;

    void m_info(t_symbol* s, const AtomList& l);
    void m_newfile(t_symbol* s, const AtomList& l);
    void m_clear(t_symbol* s, const AtomList& l);
    void m_read(t_symbol* s, const AtomList& l);
};

#endif // SDIF_FILE_H
