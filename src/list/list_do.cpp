#include "list_do.h"

static bool is_valid_step(int v)
{
    return v > 0 && v < 1024;
}

extern "C" void setup_list0x2edo()
{
    ObjectFactory<ListDo>("list.do");
}

ListDo::ListDo(const PdArgs& a)
    : BaseObject(a)
{
    createInlet();
    createOutlet();
    createOutlet();
}

void ListDo::onList(const AtomList& l)
{
    mapped_list_.clear();

    for (size_t i = 0; i < l.size(); i += 1) {
        AtomList ll = AtomList(Atom(l[i]));
        ll.append(i);
        ll.append(l.size());
        listTo(1, ll);
    }

    listTo(0, mapped_list_);
}

void ListDo::onInlet(size_t n, const AtomList& l)
{
    if (n != 1)
        return;

    if (l.empty())
        return;

    for (size_t i = 0; i < l.size(); i++)
        mapped_list_.append(l[i]);
}
