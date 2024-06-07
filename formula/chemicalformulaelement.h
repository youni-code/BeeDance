#ifndef CHEMICALFORMULAELEMENT_H
#define CHEMICALFORMULAELEMENT_H
#include "element.h"

class ChemicalFormulaElement
{
    Element elem_;
    double index_;
public:
    ChemicalFormulaElement(Element element, double index = 0.0);

    Element element() const             { return elem_; }
    void element(Element element)       { elem_ = element; }

    double index() const                { return index_; }
    void index(double index)            { index_ = index; }

    double mass() const                 { return index_ * elem_.mass(); }

    void plus(double add)               { index_ += add; }
    void mult(double mul)               { index_ *= mul; }
    bool is_empty() const               { return elem_.is_empty(); }
};

#endif // CHEMICALFORMULAELEMENT_H
