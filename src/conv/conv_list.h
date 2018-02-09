#ifndef CONV_LIST_H
#define CONV_LIST_H

#include "../img/image_data_type.h"
#include "../json/json_data_type.h"
#include "../mlist/mlist_data_type.h"

#include "ceammc_atomlist.h"

class ConvList {
    ConvList() = delete;

public:
    static DataTypeImage* toImage(AtomList* list);
    static DataTypeJSON* toJSON(AtomList *list);

    static std::string toJSONString(AtomList* l);
};

#endif // CONVMLIST_H
