#include "chemicalformulaelement.h"

// ChemicalFormulaElement::ChemicalFormulaElement() {}

ChemicalFormulaElement::ChemicalFormulaElement(Element element, double index)
{
    element_ = new Element(element);
    index_ = index;
}

ChemicalFormulaElement::~ChemicalFormulaElement()
{
    // if(element_ != nullptr)
    //     delete element_;
    // return;
}



