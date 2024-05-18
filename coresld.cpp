#include "coresld.h"

double CoreSLD::full_mass(QString line)
{
    double mass(0.0);
    auto vec_elems = to_chemical_formula_element(multiformula_to_singleformula(line));
    for(auto &it : vec_elems)
        mass += it.index() * it.mass();

    return mass;
}

double CoreSLD::read_value_squarebrackets(QString line)
{
    qDebug() << line;
    if(line.last(1) == "]") line.chop(1);
    return line.split('[').last().toDouble();
}

std::vector<SimpleFormulaElement> CoreSLD::subcalculate_subline(QString line)
{
    double brackets_value = read_value_squarebrackets(line);

    QString formula =line.split('[').first();
    double mass = full_mass(formula);
    double koef = brackets_value / mass;

    ChemicalFormula chem_f(formula);
    auto elements = chem_f.getElements();
    chem_f.multiple_by_index(elements, koef);

    return elements;
}

std::vector<ChemicalFormulaElement> CoreSLD::to_chemical_formula_element(std::vector<SimpleFormulaElement> vec)
{
    std::vector<ChemicalFormulaElement> result;
    if(!is_line_correct()) return result;

    for(auto &it: vec)
        result.push_back(ChemicalFormulaElement(dt_sld->get_element(it), it.index()));

    return result;
}

std::vector<SimpleFormulaElement> CoreSLD::multiformula_to_singleformula(QString line)
{
    qDebug() << "multitosingle: " << line;
    if(!isMultiFormula(line))
    {
        qDebug() << "It is single formula";
        chem_formula->setFormula(line);
        return chem_formula->getElements();
    }
    qDebug() << "It is multiformula";

    QStringList list_formuls = line.split(']');
    list_formuls.removeLast();

    std::vector<SimpleFormulaElement> formula_for_single;
    for(auto &it : list_formuls)
    {
        auto temp_elements = subcalculate_subline(it);
        formula_for_single.insert(formula_for_single.cend(), temp_elements.cbegin(), temp_elements.cend());
    }

    qDebug() << "elements: ";
    for(auto &it : formula_for_single) qDebug() << it.symbol();

    return formula_for_single;
}

CoreSLD::CoreSLD()
{
    chem_formula = new ChemicalFormula();
    dt_sld = new DataTableSLD();
    calc_sld = new CalculationSLD();
}
bool CoreSLD::is_all_data_exist()
{
    auto elements = chem_formula->getElements();

    for(auto const &it : elements)
        if(dt_sld->get_element(it.symbol(), it.nucleons()).is_empty())
            return false;

    return true;
}

void CoreSLD::setFormula(QString formula)
{
    str_formula = formula;

    // chem_formula->setFormula(formula);
    // chem_formula->setFormula(formula);
    calc_sld->set_elements(to_chemical_formula_element(multiformula_to_singleformula(formula)));
}
void CoreSLD::setDensity(double density)
{
    density_ = density;
    calc_sld->set_density(density_);
}

void CoreSLD::setLambda(double lambda)
{
    calc_sld->set_lambda(lambda);
}


















