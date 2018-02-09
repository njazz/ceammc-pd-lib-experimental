#ifndef CONV_IMAGE_H
#define CONV_IMAGE_H

#include "../mlist/mlist_data_type.h"
#include "../img/image_data_type.h"
#include "../json/json_data_type.h"

#include "ceammc_atomlist.h"

class ConvImage
{
    ConvImage() = delete;
public:
    static AtomList* toList(DataTypeImage* image);
    static DataTypeMList* toMList(DataTypeImage* image);

    //static DataTypeJSON* toJSON(DataTypeImage* image);
};

#endif // CONV_IMAGE_H
