#include "conv_matrix.h"
#include "ceammc_dataatom.h"
#include "ceammc_log.h"

DataTypeImage* ConvMatrix::toImage(DataTypeMatrix* matrix)
{
    DataTypeImage* ret;

    if (!matrix) {
        LIB_ERR << "bad matrix data";
        return 0;
    }

    int w = matrix->columns();
    int h = matrix->rows();

    LIB_DBG << "w h " << w << " " << h;


    ret = new DataTypeImage(new CImg<unsigned char>(w, h));

    for (int y = 0; y < h; y++) {


        for (int x = 0; x < w; x++) {

            unsigned char c = *(matrix->at(x,y));

            ret->img()->set_linear_atXY(c, x, y);
        }
    }

    return ret;
}

//DataTypeJSON* ConvMList::toJSON(DataTypeMList* mlist)
//{
//    DataTypeJSON* ret;

//    return ret;
//}

//AtomList* ConvMList::toLlll(DataTypeMList* mlist)
//{
//    AtomList* ret = new AtomList(Atom(gensym("(")));
//    AtomList* list = mlist->list();
//    //
//    for (int i = 0; i < list->size(); i++) {

//        if (list->at(i).isData()) {
//            DataAtom da = DataAtom(list->at(i));
//            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

//            if (s) {
//                AtomList sl = AtomList(*s->list());
//                AtomList* e = ConvMList::toLlll(s); //s->toLlll();

//                for (int j = 0; j < e->size(); j++) {
//                    ret->append(e->at(j));
//                }
//            } else {
//                ret->append(list->at(i));
//            }
//        } else {
//            ret->append(list->at(i));
//        }
//    }

//    //
//    ret->append((Atom(gensym(")"))));
//    return ret;
//}

//AtomList* ConvMList::toFlatList(DataTypeMList* mlist)
//{
//    AtomList* ret = new AtomList();
//    AtomList* list = mlist->list();
//    //
//    for (int i = 0; i < list->size(); i++) {

//        if (list->at(i).isData()) {
//            DataAtom da = DataAtom(list->at(i));
//            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

//            if (s) {
//                AtomList sl = AtomList(*s->list());
//                AtomList* e = ConvMList::toFlatList(s); //s->toFlatList();

//                for (int j = 0; j < e->size(); j++) {
//                    ret->append(e->at(j));
//                }
//            } else {
//                ret->append(list->at(i));
//            }
//        } else {
//            ret->append(list->at(i));
//        }
//    }

//    //
//    return ret;
//}

//std::string ConvMList::toJSONString(DataTypeMList* mlist)
//{
//    AtomList* list = mlist->list();

//    std::string ret = "[";
//    //
//    for (int i = 0; i < list->size(); i++) {

//        if (list->at(i).isData()) {
//            DataAtom da = DataAtom(list->at(i));

//            if (da.data()->type() == DataTypeMList::dataType) {
//                DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

//                std::string e = ConvMList::toJSONString(s); //s->toJSONString();
//                ret += e;

//                if (i < (list->size() - 1))
//                    ret += ",";

//                continue;
//            }
//            else {

//                if (da.data()->type() == DataTypeJSON::dataType)
//                    ret += da.data()->toString();
//                else
//                    ret += "\"" + da.data()->toString() + "\"";

//            }
//        }

//        if (list->at(i).isSymbol())
//            ret += "\"" + list->at(i).asString() + "\"";
//        else
//            ret += list->at(i).asString();

//        if (i < (list->size() - 1))
//            ret += ",";
//    }
//    //
//    ret += "]";
//    return ret;
//}
