#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "../mlist/mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "mlist_image.h"

#include "math.h"



using namespace cimg_library;

using namespace ceammc;

MListImage::MListImage(const PdArgs& args)
    : BaseObject(args)
    , _MList(new DataTypeMList(0))
    , _dPtr(new DataPtr(_MList))
{
    _out1 = createOutlet();
}

void MListImage::onBang()
{
    if (!_img) return;

    int w = _img->width();
    int h = _img->height();

    AtomList* ret = new AtomList();

    for (int i=0;i<h;i++)
    {
        AtomList* sL = new AtomList();
        for (int j=0;j<w;j++)
        {
            sL->append(Atom(float(_img->atXY(i,j))));
        }
        DataTypeMList* ml = new DataTypeMList(sL);
        DataAtom *da = new DataAtom(ml);
        ret->append(da->toAtom());
    }

    ret->output(_out1);
    //delete ret;
};



//void MListImage::onList(const AtomList& l)
//{
//    //    if (l.size() == 1)
//    //        if (l.at(0).isData()) {
//    //            onData(DataAtom(l.at(0)).data());
//    //            return;
//    //        }

//    AtomList* nl = new AtomList(l);
//    _MList = new DataTypeMList(nl);
//    _dPtr = new DataPtr(_MList);

//    _outputData = true;
//    dataTo(0, *_dPtr);
//}

//void MListImage::onFloat(float f)
//{
//    onList(AtomList(Atom(f)));
//}

//void MListImage::onSymbol(t_symbol* s)
//{
//    onList(AtomList(Atom(s)));
//}

void MListImage::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _MList->toString();
}

// ==========
void MListImage::m_read(t_symbol* s, const AtomList& l)
{
    if (l.size()<1)
        return;

    try{

    _img = new CImg<unsigned char>(l.at(0).asString().c_str());
    post("loaded [%i,%i]", _img->width(), _img->height());
    }
    catch(std::exception&e)
    {
       error("error: %s", e.what());
       _img = 0;
    }

}
void MListImage::m_write(t_symbol* s, const AtomList& l)
{}

// ==========

extern "C" {
void setup_mlist_image()
{
    ObjectFactory<MListImage> f("mlist.image");

    f.addMethod("read",&MListImage::m_read);
}
}

// ==========
