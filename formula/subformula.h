#ifndef SUBFORMULA_H
#define SUBFORMULA_H
#include <QString>
#include "chemicalformulaelement.h"

class SubFormula
{
    double index = 1.0;
    SubFormula *parent;
    std::vector<SubFormula*> children;

    std::vector<ChemicalFormulaElement> elements;

public:
    SubFormula(SubFormula* parent_sf = nullptr) : parent(parent_sf) { ; }
    ~SubFormula();
    SubFormula* back()                              { return parent; }
    SubFormula* add_subformula()                    { children.push_back(new SubFormula(this)); return children.back(); }

    void add_elem(ChemicalFormulaElement e)         { elements.push_back(e); }
    void set_index(double ind)                      { index = ind; }

    double summ_index();
    double summ_mass();

    std::vector<ChemicalFormulaElement> get_elements();
    void clear();
    bool empty();
};

#endif // SUBFORMULA_H
