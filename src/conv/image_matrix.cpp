#include "ceammc_data.h"
#include "ceammc_factory.h"

//#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "image_matrix.h"

#include "math.h"

#include "conv_image.h"

using namespace cimg_library;

using namespace ceammc;

ImageToMatrix::ImageToMatrix(const PdArgs& args)
    : BaseObject(args)
    , _matrix(new DataTypeMatrix(0,0))
    , _dPtr(new DataPtr(_matrix))
{
    _out1 = createOutlet();
}

void ImageToMatrix::onBang()
{
    if (!_matrix->dataSize())
        return;

    AtomList(DataAtom(*_dPtr).toAtom()).output(_out1);
};

void ImageToMatrix::onData(const DataPtr& d)
{
    DataTypeImage* img = const_cast<DataTypeImage*>(d.as<DataTypeImage>());

    DataTypeMatrix* matrix = ConvImage::toMatrix(img);
    if (!matrix)
        return;
    _matrix = matrix;
    _dPtr = new DataPtr(_matrix);
    onBang();
}

void ImageToMatrix::onList(const AtomList& l)
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

void ImageToMatrix::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _matrix->toString();
}

// ==========

extern "C" {
void setup_conv_image_matrix()
{
    ObjectFactory<ImageToMatrix> f("conv.image->matrix");
    f.addAlias("image->matrix");
}
}

// ==========
