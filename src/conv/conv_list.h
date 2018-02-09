#ifndef CONVMLIST_H
#define CONVMLIST_H

#include "../img/image_data_type.h"
#include "../json/json_data_type.h"
#include "../mlist/mlist_data_type.h"

#include "ceammc_atomlist.h"

class ConvList {
    ConvList() = delete;

public:
    static DataTypeImage* toImage(AtomList* list);
    static DataTypeJSON* toJSON(AtomList *list);
    static DataTypeMList* toMList(AtomList* list);

    static std::string toJSONString(AtomList* mlist);
};

#endif // CONVMLIST_H
