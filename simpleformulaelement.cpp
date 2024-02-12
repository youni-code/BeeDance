#include "simpleformulaelement.h"


SimpleFormulaElement::SimpleFormulaElement(const QString symb, const unsigned long count, double ind)
{
    symbol_ = symb;
    nucleons_ = count;
    index_ = ind;
    return;
}

bool SimpleFormulaElement::operator==(const SimpleFormulaElement& right) const
{
    return (this->symbol_ == right.symbol_ && this->nucleons_ == right.nucleons_);
}

bool SimpleFormulaElement::operator!=(const SimpleFormulaElement & right) const
{
    return !(*this == right);
}

bool SimpleFormulaElement::operator<(SimpleFormulaElement& right)
{
    if(this->symbol_ < right.symbol_) return true;
    if(this->symbol_ > right.symbol_) return false;
    // if lines equal
    if(this->nucleons_ < right.nucleons_) return true;

    return false;
}
