#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "matrix_data_type.h"

#include "ceammc_dataatom.h"

#include "matrix_obj.h"

#include "math.h"

using namespace ceammc;

MatrixObj::MatrixObj(const PdArgs& args)
    : BaseObject(args)
    , _matrix(new DataTypeMatrix(0, 0))
    , _dPtr(new DataPtr(_matrix))
{
    _out1 = createOutlet();
}

void MatrixObj::onBang()
{
    if (_matrix->dataSize() == 0)
        return;

    dataTo(0, *_dPtr);
};

void MatrixObj::onData(const DataPtr& d)
{
    if (!d.as<DataTypeMatrix>())
        return;

    DataTypeMatrix* matrix = const_cast<DataTypeMatrix*>(d.as<DataTypeMatrix>());
    if (!matrix)
        return;
    _matrix = matrix;
    _dPtr = new DataPtr(_matrix);

    onBang();
}

void MatrixObj::onList(const AtomList& l)
{
    if (l.size() == 1)
        if (l.at(0).isData()) {
            onData(DataAtom(l.at(0)).data());
            return;
        }
}

void MatrixObj::m_new(t_symbol* s, const AtomList& l)
{
    if (l.size() < 2)
        return;

    size_t w = l[0].asSizeT();
    size_t h = l[0].asSizeT();

    _matrix = new DataTypeMatrix(w, h);
    _dPtr = new DataPtr(_matrix);
}
void MatrixObj::onFloat(float f)
{
    onList(AtomList(Atom(f)));
}

void MatrixObj::onSymbol(t_symbol* s)
{
    onList(AtomList(Atom(s)));
}

void MatrixObj::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr->desc().id;
    OBJ_DBG << "refcount: " << _dPtr->refCount();
    OBJ_DBG << "contents:  " << _matrix->toString();
}

// ==========

extern "C" {
void setup_matrix()
{
    ObjectFactory<MatrixObj> f("matrix");
    f.addMethod("new", &MatrixObj::m_new);
}
}

// ==========
