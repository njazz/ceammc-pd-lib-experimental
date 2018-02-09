#ifndef JSON_OBJ_H
#define JSON_OBJ_H

#include "ceammc_object.h"

#include "../mlist/mlist_data_type.h"

class JSONToMList : public BaseObject {
    t_outlet* _out1;

    DataTypeMList* _mlist;
    DataPtr* _dPtr = 0;

public:
    JSONToMList(const PdArgs& args);

    //    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onBang() override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;
};

#endif // SDIF_FILE_H
