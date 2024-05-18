#include "element.h"


void Element::mass(double value)
{
    is_mass_ = true;
    mass_ = value;
}


void Element::bc_comp(std::complex<double> value)
{
    is_bc_ = true;
    bc_comp_ = value;
}

void Element::bi_comp(std::complex<double> value)
{
    is_bi_ = true;
    bi_comp_ = value;
}

void Element::sigma_a(double value)
{
    is_sigma_a_ = true;
    sigma_a_ = value;
}

void Element::sigma_i(double value)
{
    is_sigma_i_ = true;
    sigma_i_ = value;
}


Element::Element(QString elem, unsigned long atom_num, unsigned long c_nucleons)
{
    symbol_ = elem;
    atomic_number_ = atom_num;
    count_nucleons_ = c_nucleons;

    is_mass_ = false;
    is_bc_ = false;
    is_bi_ = false;
    is_sigma_a_ = false;
    is_sigma_i_ = false;
    is_conc_ = false;
    is_atomic_mass_ = false;
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
