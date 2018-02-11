#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"
#include "matrix_data_type.h"

class MatrixObj : public BaseObject {
    t_outlet* _out1;

    DataTypeMatrix* _matrix;
    DataPtr* _dPtr = 0;



public:
    MatrixObj(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onData(const DataPtr &) override;
    virtual void onList(const AtomList& l) override;

    virtual void onFloat(float f) override;
    virtual void onSymbol(t_symbol* s) override;

    void m_new(t_symbol* s, const AtomList& l);

};

#endif // SDIF_FILE_H
