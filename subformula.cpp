#include "subformula.h"


SubFormula::~SubFormula()
{
    clear();
}

double SubFormula::summ_index()
{
    double summ(0.0);
    for(auto &e : elements)
        summ += e.index();
    for(auto &child : children)
        summ += child->summ_index();

    return index * summ;
}

double SubFormula::summ_mass()
{
    double summ(0.0);
    for(auto &e : elements)
        summ += e.mass();
    for(auto &child : children)
        summ += child->summ_mass();

    return index * summ;
}


std::vector<ChemicalFormulaElement> SubFormula::get_elements()
{
    auto result = elements;

    for(auto &it : children)
    {
        auto vec = it->get_elements();
        result.insert(result.end(), vec.begin(), vec.end());
    }
    for(auto &it : result)
        it.mult(index);

    return result;
}

void SubFormula::clear()
{
    for(auto p : children)
        p->clear();
    for(auto p : children)
        delete p;

    children.clear();
    elements.clear();
}

bool SubFormula::empty()
{
    return children.empty() &&  elements.empty();
}
