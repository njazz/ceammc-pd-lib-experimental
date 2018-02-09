#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../img/image_data_type.h"
#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "mlist_image.h"

#include "math.h"

#include "conv_mlist.h"

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

//    DataTypeMList* ml = const_cast<DataTypeMList*>(DataAtom(l.at(0)).data().as<DataTypeMList>());
//    if (!ml) {
//        error("first element is not an mlist");
//        return;
//    }


    DataTypeMList*ml = new DataTypeMList(new AtomList(l));

//    int w = DataTypeMList(new AtomList(l)).minimalSublistLength();
//    int h = l.size();

//    post("w h %i %i", w, h);

//    DataTypeImage* im = new DataTypeImage(new CImg<unsigned char>(w, h));

//    for (int i = 0; i < h; i++) {
//        DataTypeMList* nl = const_cast<DataTypeMList*>(DataAtom(l.at(i)).data().as<DataTypeMList>());
//        if (!nl)
//            return;

//        AtomList* sL = nl->list();

//        if (sL->size() < w) {
//            error("mlist length is less than expected");
//            return;
//        }

//        for (int j = 0; j < w; j++) {

//            unsigned char c = sL->at(j).asFloat();

//            im->img()->set_linear_atXY(c, j, i);
//        }
//    }

    DataTypeImage* img = ConvMList::toImage(ml);
    if (!img) return;

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
