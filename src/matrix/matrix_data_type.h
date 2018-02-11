#ifndef MATRIX_DATA_TYPES_H
#define MATRIX_DATA_TYPES_H

#include "ceammc_data.h"


using namespace ceammc;

class DataTypeMatrix : public AbstractData {
    float* _data = 0;

    size_t _columns = 0;
    size_t _rows = 0;
    

public:
    static const DataType dataType = 301;

    explicit DataTypeMatrix(int columns, int rows);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;
    
    inline size_t columns(){return _columns;}
    inline size_t rows(){return _rows;}

    inline size_t dataSize(){return _columns*_rows;}

    const float* at(int x, int y);
    void set(int x, int y, float v);
    
    const float* rowAt(int y);
    
};

#endif // MATRIX_DATA_TYPES_H
