#include "ceammc_data.h"
#include "ceammc_factory.h"

#include "mlist_data_type.h"

#include "ceammc_dataatom.h"

#include "mlist_flip.h"

#include "math.h"

using namespace ceammc;

MListFlip::MListFlip(const PdArgs& args)
    : BaseObject(args)
    , _MList(new DataTypeMList(0))
    , _dPtr(_MList)
{
    _out1 = createOutlet();
}

void MListFlip::onBang()
{
    if (!_MList)
        return;

    AtomList* o = new AtomList(_dPtr.asAtom());
    o->output(_out1);
}

void MListFlip::onList(const AtomList& l)
{

    AtomList l1 = AtomList(l);

    _MList = new DataTypeMList(&l1);
    AtomList* o = _MList->flip();
    _MList = new DataTypeMList(o);
    o->output(_out1);

    _dPtr = DataPtr(_MList);
}

void MListFlip::dump() const
{
    OBJ_DBG << "DATA: MList";
    BaseObject::dump();
    OBJ_DBG << "id:       " << _dPtr.desc().id;
    OBJ_DBG << "refcount: " << _dPtr.refCount();
    OBJ_DBG << "contents:  " << _MList->toString();
}

// ==========

extern "C" {
void setup_mlist0x2eflip()
{
    ObjectFactory<MListFlip> f("mlist.flip");
}
}

// ==========
