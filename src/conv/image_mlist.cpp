#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "image_mlist.h"

#include "math.h"

using namespace cimg_library;

using namespace ceammc;

ImageToMlist::ImageToMlist(const PdArgs& args)
    : BaseObject(args)
    , _MList(new DataTypeMList(0))
    , _dPtr(new DataPtr(_MList))
{
    _out1 = createOutlet();
}

void ImageToMlist::onBang()
{
    if (!_MList->list()) return;
    _MList->list()->output(_out1);
};

void ImageToMlist::onData(const DataPtr& d)
{
    DataTypeImage* img = const_cast<DataTypeImage*>(d.as<DataTypeImage>());

    if (!img)
        return;

    if (!img->img())
        return;

    int w = img->img()->width();
    int h = img->img()->height();

    post("got image %i %i", w, h);
    AtomList* ret = new AtomList();

    for (int i = 0; i < h; i++) {
        AtomList* sL = new AtomList();
        for (int j = 0; j < w; j++) {
            sL->append(Atom(float(img->img()->atXY(j, i))));
        }
        DataTypeMList* ml = new DataTypeMList(sL);
        DataAtom* da = new DataAtom(ml);
        ret->append(da->toAtom());
    }

    _MList = new DataTypeMList(ret);
    _dPtr = new DataPtr(_MList);
}

void ImageToMlist::onList(const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {

            DataTypeImage* img = const_cast<DataTypeImage*>(DataAtom(l.at(0)).data().as<DataTypeImage>());

            post("img %lu", (long)img);

            if (img)
                if (img->img())
                    post("img: %i %i", img->img()->width(), img->img()->height());

            onData(DataAtom(l.at(0)).data());
            return;
        }
}

void ImageToMlist::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _MList->toString();
}

// ==========

extern "C" {
void setup_conv_image_mlist()
{
    ObjectFactory<ImageToMlist> f("conv.image->mlist");
    f.addAlias("image->mlist");
}
}

// ==========
