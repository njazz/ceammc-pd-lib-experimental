#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"

#include "sublist_data_type.h"

class SublistLlll : public BaseObject {
    t_outlet* _out1;

    DataTypeSubList* _sublist;
    DataPtr _dPtr;

    bool _outputData = false;

public:
    SublistLlll(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;
    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;
};

#endif // SDIF_FILE_H
