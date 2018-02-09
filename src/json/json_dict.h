#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "ceammc_object.h"
#include "json_data_type.h"

class JSONDict : public BaseObject {
    t_outlet* _out1;

    DataTypeJSON* _JSON;
    DataPtr* _dPtr = 0;

public:
    JSONDict(const PdArgs& args);

    virtual void dump() const override;

    virtual void onBang() override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;

    void m_get_list(t_symbol* s, const AtomList& l);
    void m_set_list(t_symbol* s, const AtomList& l);

    void m_get_mlist(t_symbol* s, const AtomList& l);
    void m_set_mlist(t_symbol* s, const AtomList& l);

    void m_get_json(t_symbol* s, const AtomList& l);
    void m_set_json(t_symbol* s, const AtomList& l);

    void m_clear(t_symbol* s, const AtomList& l);
};

#endif // SDIF_FILE_H
