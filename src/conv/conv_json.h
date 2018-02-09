#ifndef CONVMLIST_H
#define CONVMLIST_H

#include "../mlist/mlist_data_type.h"
#include "../img/image_data_type.h"
#include "../json/json_data_type.h"

#include "ceammc_atomlist.h"

class ConvJSON
{
    ConvJSON() = delete;
public:
    static DataTypeMList *toMList(DataTypeJSON* json);
    static AtomList* toList(DataTypeJSON* json);

};

#endif // CONVMLIST_H
