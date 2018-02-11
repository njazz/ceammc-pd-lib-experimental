#ifndef MLIST_IMAGE_H
#define SDIF_FILE_H

#include "../img/image_data_type.h"
#include "../matrix/matrix_data_type.h"
#include "ceammc_object.h"

#define cimg_OS 0
//#define cimg_use_png 1
#define cimg_use_cpp11 1
#define cimg_use_jpeg 1
#include "../img/CImg.h"

class ImageToMatrix : public BaseObject {
    t_outlet* _out1;

    DataTypeMatrix* _matrix;
    DataPtr* _dPtr = 0;

public:
    ImageToMatrix(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onData(const DataPtr& d) override;
    virtual void onList(const AtomList& l) override;
};

#endif // SDIF_FILE_H
