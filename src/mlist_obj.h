#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"

#include "mlist_data_type.h"

class MListObj : public BaseObject {
    t_outlet* _out1;

    DataTypeMList* _MList;
    DataPtr* _dPtr = 0;

    bool _outputData = false;

public:
    MListObj(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;
    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;
};

#endif // SDIF_FILE_H
