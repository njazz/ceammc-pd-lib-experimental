#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../img/image_data_type.h"
#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "mlist_image.h"

#include "math.h"

#include "conv_list.h"

using namespace cimg_library;
using namespace ceammc;

MListToImage::MListToImage(const PdArgs& args)
    : BaseObject(args)
    , _img(new DataTypeImage(0))
    , _dPtr(new DataPtr(_img))
{
    _out1 = createOutlet();
}

void MListToImage::onBang()
{
    if (!_img->img())
        return;

    int w = _img->img()->width();
    int h = _img->img()->height();

    post("out img %i %i", w, h);

    AtomList* ret = new AtomList((new DataAtom(*_dPtr))->toAtom());
    ret->output(_out1);
};

void MListToImage::onList(const AtomList& l)
{
    if (l.size() < 1) {
        error("input list empty");
        return;
    }

    if (!l.at(0).isData()) {
        error("first element is not a data/mlist");
        return;
    }

    DataTypeImage* img = ConvList::toImage(new AtomList(l));
    if (!img)
        return;

    _img = img;
    _dPtr = new DataPtr(_img);
    onBang();
}

void MListToImage::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _img->toString();
}

// ==========

extern "C" {
void setup_conv_mlist_image()
{
    ObjectFactory<MListToImage> f("conv.mlist->image");
    f.addAlias("mlist->image");
}
}

// ==========
