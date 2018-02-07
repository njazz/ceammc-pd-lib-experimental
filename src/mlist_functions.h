#ifndef MLIST_FUNCTIONS_H
#define MLIST_FUNCTIONS_H

AtomList* convertList(AtomList src)
{
    AtomList* ret = new AtomList(Atom(gensym("(")));
    //
    for (int i = 0; i < src.size(); i++) {

        if (src.at(i).isData()) {
            DataAtom da = DataAtom(src.at(i));
            DataTypeMList* s = const_cast<DataTypeMList*>(da.data().as<DataTypeMList>());

            if (s) {
                AtomList sl = AtomList(*s->list());
                AtomList* e = convertList(sl);

                for (int j = 0; j < e->size(); j++) {
                    ret->append(e->at(j));
                }
            } else {
                ret->append(src.at(i));
            }
        } else {
            ret->append(src.at(i));
        }
    }

    //
    ret->append((Atom(gensym(")"))));
    return ret;
}

#endif // MLIST_FUNCTIONS_H
