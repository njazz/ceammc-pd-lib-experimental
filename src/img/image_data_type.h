#ifndef JSON_DATA_TYPES_H
#define JSON_DATA_TYPES_H

#include "ceammc_data.h"
#include "ceammc_atomlist.h"

// TODO
#define cimg_OS 0
//#define cimg_use_png 1
#define cimg_use_cpp11 1
#define cimg_use_jpeg 1
#include "CImg.h"

using namespace ceammc;
using namespace cimg_library;

static const ::ceammc::DataType DATA_IMAGE = 200;

class DataTypeImage : public AbstractData {
    CImg<unsigned char>* _img = 0;

public:
    static const DataType dataType = DATA_IMAGE;

    explicit DataTypeImage(CImg<unsigned char>* img);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    CImg<unsigned char>* img() { return _img; }
};

#endif // SDIF_DATA_TYPES_H
