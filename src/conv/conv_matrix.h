#ifndef CONV_MATRIX_H
#define CONV_MATRIX_H

#include "../mlist/mlist_data_type.h"
#include "../img/image_data_type.h"
#include "../json/json_data_type.h"
#include "../matrix/matrix_data_type.h"

#include "ceammc_atomlist.h"

class ConvMatrix
{
    ConvMatrix() = delete;
public:
    static DataTypeImage* toImage(DataTypeMatrix* matrix);

    //    static DataTypeJSON* toJSON(DataTypeMList* mlist);
    //    static AtomList* toLlll(DataTypeMList* mlist);
    //    static AtomList* toFlatList(DataTypeMList *mlist);
    //    static std::string toJSONString(DataTypeMList* mlist);


};

#endif // CONVMLIST_H
