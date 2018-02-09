#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "ceammc_object.h"

#include "../json/json_data_type.h"

class ListToJSON : public BaseObject {
    t_outlet* _out1;

    DataTypeJSON* _json;
    DataPtr* _dPtr = 0;

public:
    ListToJSON(const PdArgs& args);

    //    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;

    virtual void onBang() override;
};

#endif // SDIF_FILE_H
