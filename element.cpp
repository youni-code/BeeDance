#include "element.h"


void Element::set_mass(double value)
{
    is_mass = true;
    mass_ = value;
}

void Element::set_bc(std::complex<double> value)
{
    is_bc = true;
    bc_ = value;
}

void Element::set_bi(std::complex<double> value)
{
    is_bi = true;
    bi_ = value;
}

void Element::set_sigmaa(double value)
{
    is_sigma_a = true;
    sigma_a_ = value;
}

void Element::set_sigmai(double value)
{
    is_sigma_i = true;
    sigma_i_ = value;
}


Element::Element(QString elem, unsigned long atom_num, unsigned long c_nucleons)
{
    symbol_ = elem;
    atomic_number_ = atom_num;
    count_nucleons_ = c_nucleons;

    is_mass = false;
    is_bc = false;
    is_bi = false;
    is_sigma_a = false;
    is_sigma_i = false;
}

bool Element::operator==(const Element &el) const
{
    if(this->symbol_ == el.symbol_ && this->count_nucleons_ == el.count_nucleons_)
        return true;

    return false;
}
bool Element::operator!=(const Element &el) const
{
    return ((*this) == el);
}
