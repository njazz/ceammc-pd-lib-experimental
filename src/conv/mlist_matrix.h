#ifndef SDIF_FILE_H
#define SDIF_FILE_H

#include "ceammc_object.h"
#include "../mlist/mlist_data_type.h"
#include "../img/image_data_type.h"

#define cimg_OS 0
//#define cimg_use_png 1
#define cimg_use_cpp11 1
#define cimg_use_jpeg 1
#include "../img/CImg.h"

class MListToImage : public BaseObject {
    t_outlet* _out1;

    DataTypeImage* _img;
    DataPtr* _dPtr = 0;


public:
    MListToImage(const PdArgs& args);

    virtual void onBang() override;
    virtual void dump() const override;

    virtual void onList(const AtomList& l) override;
//    virtual void onData(const AtomList& l) override;

};

#endif // SDIF_FILE_H
