#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "image_mlist.h"

#include "math.h"

#include "conv_image.h"

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

    DataTypeMList*mlist = ConvImage::toMList(img);
    if (!mlist) return;
    _MList = mlist;
    _dPtr = new DataPtr(_MList);
    onBang();
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
