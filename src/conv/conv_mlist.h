#ifndef CONVMLIST_H
#define CONVMLIST_H

#include "../mlist/mlist_data_type.h"
#include "../img/image_data_type.h"
#include "../json/json_data_type.h"

#include "ceammc_atomlist.h"

class ConvMList
{
    ConvMList() = delete;
public:
    static DataTypeImage* toImage(DataTypeMList* mlist);
    static DataTypeJSON* toJSON(DataTypeMList* mlist);

    static AtomList* toLlll(DataTypeMList* mlist);
    static AtomList* toFlatList(DataTypeMList *mlist);

    static std::string toJSONString(DataTypeMList* mlist);
};

#endif // CONVMLIST_H
