#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"

#include "../json/json_data_type.h"

class MListToJSON : public BaseObject {
    t_outlet* _out1;

    DataTypeJSON* _json;
    DataPtr* _dPtr;

public:
    MListToJSON(const PdArgs& args);

    virtual void onBang() override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;

    virtual void onFloat(float f) override;
    virtual void onSymbol(t_symbol* s) override;

    virtual void dump() const override;
};

#endif // SDIF_FILE_H
