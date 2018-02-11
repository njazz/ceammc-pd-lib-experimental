#include "conv_image.h"
#include "ceammc_log.h"
#include "ceammc_dataatom.h"

AtomList* ConvImage::toList(DataTypeImage* image)
{
    AtomList* ret = new AtomList();

    if (!image) {
        LIB_ERR << "bad image data";
        return 0;
    }

    if (!image->img()) {
        LIB_ERR << "bad image data pointer";
        return 0;
    }

    int w = image->img()->width();
    int h = image->img()->height();

    for (int i = 0; i < h; i++) {
        AtomList* subList = new AtomList();
        for (int j = 0; j < w; j++) {
            subList->append(Atom(float(image->img()->atXY(j, i))));
        }
        DataTypeMList* mlist = new DataTypeMList(subList);
        DataAtom* dataAtom = new DataAtom(mlist);
        ret->append(dataAtom->toAtom());
    }
    return ret;
}

DataTypeMList* ConvImage::toMList(DataTypeImage* image)
{
    return new DataTypeMList(ConvImage::toList(image));
}

DataTypeMatrix* ConvImage::toMatrix(DataTypeImage* image)
{
    if (!image) {
        LIB_ERR << "bad image data";
        return 0;
    }

    if (!image->img()) {
        LIB_ERR << "bad image data pointer";
        return 0;
    }

    int w = image->img()->width();
    int h = image->img()->height();

    DataTypeMatrix* ret = new DataTypeMatrix(w,h);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ret->set(x,y, float(image->img()->atXY(x, y)));
        }

    }
    return ret;
}
