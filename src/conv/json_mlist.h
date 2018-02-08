#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "ceammc_object.h"

#include "json_data_type.h"

class JSONObj : public BaseObject {
    t_outlet* _out1;

    DataTypeJSON* _JSON;
    DataPtr* _dPtr = 0;

public:
    JSONObj(const PdArgs& args);

    //    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;
};

#endif // SDIF_FILE_H
