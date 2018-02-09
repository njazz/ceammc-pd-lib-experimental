#include "conv_image.h"

#include "ceammc_log.h"

#include "ceammc_dataatom.h"

AtomList* ConvImage::toList(DataTypeImage* image)
{
    AtomList* ret;


    if (!image)
    {
        LIB_ERR << "bad image data";
        return 0;
    }

    if (!image->img())
    {
        LIB_ERR << "bad image data pointer";
        return 0;
    }

    int w = image->img()->width();
    int h = image->img()->height();

    ret = new AtomList();

    for (int i = 0; i < h; i++) {
        AtomList* sL = new AtomList();
        for (int j = 0; j < w; j++) {
            sL->append(Atom(float(image->img()->atXY(j, i))));
        }
        DataTypeMList* ml = new DataTypeMList(sL);
        DataAtom* da = new DataAtom(ml);
        ret->append(da->toAtom());
    }


    return ret;
}

DataTypeMList* ConvImage::toMList(DataTypeImage* image)
{
    return new DataTypeMList(ConvImage::toList(image));
}

//DataTypeJSON* ConvImage::toJSON(DataTypeImage* image)
//{
//    DataTypeJSON* ret;

//    return ret;
//}
