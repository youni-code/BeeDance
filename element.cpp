#include "element.h"

//Element::Element() {}



Element::Element(QString elem, unsigned long atom_num, unsigned long c_nucleons)
{
    symbol = elem;
    atomic_number = atom_num;
    count_nucleons = c_nucleons;
}
