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

//void MListFlip::onBang()
//{
//    if (_MList->list() == 0)
//        return;

//    if (_outputData)
//        dataTo(0, _dPtr);
//    else
//        _MList->list()->output(_out1);
//};

// todo: move
//AtomList* convertList(AtomList src)
//{
//    AtomList* ret = new AtomList(Atom(gensym("(")));
//    //
//    for (int i = 0; i < src.size(); i++) {

//        if (src.at(i).isData()) {
//            DataAtom da = DataAtom(src.at(i));
//            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

//            if (s) {
//                AtomList sl = AtomList(*s->list());
//                AtomList* e = convertList(sl);

//                for (int j = 0; j < e->size(); j++) {
//                    ret->append(e->at(j));
//                }
//            } else {
//                ret->append(src.at(i));
//            }
//        } else {
//            ret->append(src.at(i));
//        }
//    }

//    //
//    ret->append((Atom(gensym(")"))));
//    return ret;
//}

//void MListFlip::onData(const DataPtr& d)
//{
//    if (!d.as<DataTypeMList>())
//        return;

//    _MList = const_cast<DataTypeMList*>(d.as<DataTypeMList>());

//    convertList(AtomList(*_MList->list()))->output(_out1);
//}

int smallestSublistLength(const AtomList& l)
{
    int ret = 0;

    for (int i = 0; i < l.size(); i++) {
        if (!l.at(i).isData())
            return 1;

        if (!DataAtom(l.at(i)).data().as<DataTypeMList>())
            return 1;

        int ls = const_cast<DataTypeMList*>(DataAtom(l.at(i)).data().as<DataTypeMList>())->list()->size();

        if (!ret)
            ret = ls;
        else
            ret = (ls < ret) ? ls : ret;
    }
    return ret;
}

void MListFlip::onList(const AtomList& l)
{
    int ls = smallestSublistLength(l);

//    post("smallest len %i", ls);
    //return;

    AtomList ret;

    if (ls == 1) {
        for (int i = 0; i < l.size(); i++) {
            DataTypeMList* ml = new DataTypeMList(new AtomList(l.at(i)));
            ret.append((new DataAtom(ml))->toAtom());
        }
        ret.output(_out1);
        return;
    }

    AtomList* subLists = new AtomList[ls];

    for (int i = 0; i < l.size(); i++) {

        DataAtom*d = new DataAtom(l.at(i));
        if (!d) continue;

        const DataTypeMList* ml = d->data().as<DataTypeMList>();
        if (!ml) continue;

        AtomList* sub = const_cast<DataTypeMList*>(ml)->list();
        if (!sub) continue;

        for (int j = 0; j < ls; j++) {
            //subLists[i].append(Atom(gensym("test")));
            subLists[j].append(Atom(sub->at(j)));
        }
    }
    for (int i = 0; i < ls; i++) {
        DataTypeMList* ml = new DataTypeMList(&subLists[i]);
        ret.append((new DataAtom(ml))->toAtom());
    }

    ret.output(_out1);
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
