#include "element.h"


Element::Element(QString elem, unsigned long atom_num, unsigned long c_nucleons)
{
    symbol = elem;
    atomic_number = atom_num;
    count_nucleons = c_nucleons;

    is_mass = false;
    is_bc = false;
}

bool Element::operator==(const Element &el) const
{
    if(this->symbol == el.symbol && this->count_nucleons == el.count_nucleons)
        return true;

    return false;
}
bool Element::operator!=(const Element &el) const
{
    return ((*this) == el);
}
