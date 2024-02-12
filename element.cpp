#include "element.h"

//Element::Element() {}

void Element::initialize()
{
    is_isotope = false;
    is_conc = false;
    is_atomic_number = false;
    is_coh_b = false;
    is_coh_xs = false;
    is_inc_b = false;
    is_inc_xs = false;
    is_scatt_xs = false;
    is_abs_xs = false;
    is_mass = false;
}

bool Element::setMass(double value)
{
    mass = value;
    is_mass = true;
    return true;
}

bool Element::setConc(double co)
{
    conc = co;
    is_conc = true;
    return true;
}

bool Element::setAtomicNumber(unsigned long atom)
{
    atomic_number = atom;
    is_atomic_number = true;
    return true;
}

bool Element::setCohb(std::complex<double> value)
{
    coh_b = value;
    is_coh_b = true;

    return true;
}

bool Element::setIncb(std::complex<double> value)
{
    inc_b = value;
    is_inc_b = true;
    return true;
}

bool Element::setCohxs(double value)
{
    coh_xs = value;
    is_coh_xs = true;

    return true;
}

bool Element::setIncxs(double val)
{
    inc_xs = val;
    is_inc_xs = true;
    return true;
}

bool Element::setScattxs(double value)
{
    scatt_xs = value;
    is_scatt_xs = true;
    return true;
}

bool Element::setAbsxs(double value)
{
    abs_xs = value;
    is_abs_xs = true;
    return true;
}

QString Element::getSymbol() const
{
    return symbol;
}

double Element::getMass() const { return mass; }

double Element::getConc() const { return conc; }
unsigned long Element::getCountNucleons() const { return count_nucleons; }
unsigned long Element::getAtomicNumber() const { return atomic_number;  }
std::complex<double> Element::getCohb() const { return coh_b;  }
std::complex<double> Element::getIncb() const { return inc_b;  }
double Element::getCohxs() const { return coh_xs;  }
double Element::getScatxs() const { return scatt_xs;  }
double Element::getAbsxs() const { return abs_xs;  }


bool Element::isConc() const { return is_conc; }
bool Element::isIsotope() const { return is_isotope; }
bool Element::isCohb() const { return is_coh_b; }
bool Element::isIncb() const { return is_inc_b; }
bool Element::isCohxs() const { return is_coh_xs; }

bool Element::isInxs() const { return is_inc_xs; }
bool Element::isScattxs() const { return is_scatt_xs; }
bool Element::isAbsxs() const { return is_abs_xs; }
bool Element::isMass() const {return is_mass; }

Element::Element(QString elem, unsigned long atom_num, unsigned long count_nucleons)
{
    initialize();

    symbol = elem;
    atomic_number = atom_num;
    if(count_nucleons) is_isotope = true;
    this->count_nucleons = count_nucleons;
}
