#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../img/image_data_type.h"
#include "../matrix/matrix_data_type.h"

#include "ceammc_dataatom.h"

#include "matrix_image.h"

#include "math.h"

#include "conv_matrix.h"

using namespace cimg_library;
using namespace ceammc;

MatrixToImage::MatrixToImage(const PdArgs& args)
    : BaseObject(args)
    , _img(new DataTypeImage(0))
    , _dPtr(new DataPtr(_img))
{
    _out1 = createOutlet();
}

void MatrixToImage::onBang()
{
    if (!_img->img())
        return;

    int w = _img->img()->width();
    int h = _img->img()->height();

    post("out img %i %i", w, h);

    AtomList* ret = new AtomList((new DataAtom(*_dPtr))->toAtom());
    ret->output(_out1);
};

void MatrixToImage::onList(const AtomList& l)
{
    if (l.size() < 1) {
        error("input list empty");
        return;
    }

    if (!l.at(0).isData()) {
        error("first element is not a data/mlist");
        return;
    }

    DataTypeMatrix* matrix = const_cast<DataTypeMatrix*>(DataAtom(l.at(0)).data().as<DataTypeMatrix>());

    DataTypeImage* img = ConvMatrix::toImage(matrix);
    if (!img)
        return;

    _img = img;
    _dPtr = new DataPtr(_img);
    onBang();
}

void MatrixToImage::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _img->toString();
}

// ==========

extern "C" {
void setup_conv_matrix_image()
{
    ObjectFactory<MatrixToImage> f("conv.matrix->image");
    f.addAlias("matrix->image");
}
}

// ==========
