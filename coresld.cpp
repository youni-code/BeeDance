#include "coresld.h"

double CoreSLD::full_mass(QString line)
{
    auto temp_chem_formula = new ChemicalFormula();
    temp_chem_formula->setFormula(line);
    auto vec_elem = temp_chem_formula->getElements();

    double mass(0.0);

    for(auto it(vec_elem.cbegin()); it != vec_elem.cend(); it++)
        mass += it->index() * dt_sld->getElement(it->symbol(), it->nucleons()).get_mass();

    return mass;
}

double CoreSLD::calculate_sld(QString line)
{

    chem_formula->setFormula(line);
    calc_sld->set_density(density_);
    calc_sld->set_elements(to_chemical_formula_element(chem_formula->getElements()));

    if(!isMultiFormula(line))
        return calculate_singlesld();
    return calculate_multisld(line);
}

double CoreSLD::calculate_sld_err(QString line)
{
    chem_formula->setFormula(line);
    calc_sld->set_density(density_);
    calc_sld->set_elements(to_chemical_formula_element(chem_formula->getElements()));

    if(!isMultiFormula(line))
        return calculate_singlesld_err(line);


    return calculate_singlesld_err(line); // change
}

double CoreSLD::calculate_multisld(QString line)
{
    line.chop(1);
    QStringList list_formuls = line.split(']');

    std::vector<SimpleFormulaElement> formula_for_single;

    for(auto it(list_formuls.cbegin()); it != list_formuls.cend(); it++)
    {
        auto temp_elements = subcalculate_subline(*it);
        formula_for_single.insert(formula_for_single.cend(), temp_elements.cbegin(), temp_elements.cend());
    }

    calc_sld->set_elements(to_chemical_formula_element(formula_for_single));
    return calculate_singlesld();
}

double CoreSLD::calculate_multisld_err(QString line)
{

    return 0.0;
}


double CoreSLD::calculate_singlesld_err(QString line)
{
    chem_formula->setFormula(line);

    calc_sld->set_density(density_);
    calc_sld->set_elements(to_chemical_formula_element(chem_formula->getElements()));
    return calc_sld->get_real_sld_error();
}
double CoreSLD::calculate_singlesld_err(std::vector<SimpleFormulaElement> elem_vec)
{
    calc_sld->set_density(density_);
    calc_sld->set_elements(to_chemical_formula_element(elem_vec));
    return calc_sld->get_real_sld_error();
}

double CoreSLD::read_value_squarebrackets(QString line)
{
    QString number;
    bool inside_brackets(false);
    for(auto it(line.cbegin()); it != line.cend(); it++)
    {
        if(inside_brackets) number.push_back(*it);
        if((*it) == '[') { inside_brackets = true; }
    }
    qDebug() << number.toDouble();
    return number.toDouble();
}

std::vector<SimpleFormulaElement> CoreSLD::subcalculate_subline(QString line)
{
    double brackets_value = read_value_squarebrackets(line);
    QString formula = delete_squarebrackets(line);
    double mass = full_mass(formula);
    double koef = brackets_value / mass;

    ChemicalFormula chem_f(formula);
    auto elements = chem_f.getElements();
    chem_f.multiple_by_index(elements, koef);

    return elements;
}

QString CoreSLD::delete_squarebrackets(QString line)
{
    auto del_it = line.cend();
    for(auto it(line.cbegin()); it != line.cend(); it++)
    {
        if((*it) == '[') {del_it = it; break; }
    }
    line.erase(del_it, line.cend());

    return line;
}

std::vector<ChemicalFormulaElement> CoreSLD::to_chemical_formula_element(std::vector<SimpleFormulaElement> vec)
{
    std::vector<ChemicalFormulaElement> result;

    if(!is_line_correct())
        return result;

    for(auto &it: vec)
        result.push_back(ChemicalFormulaElement(dt_sld->getElement(it), it.index()));

    return result;
}
std::vector<ChemicalFormulaElement> CoreSLD::to_chemical_formula_element()
{
    chem_formula->setFormula(str_formula);
    return to_chemical_formula_element(chem_formula->getElements());
}

std::vector<SimpleFormulaElement> CoreSLD::multiformula_to_singleformula(QString line)
{
    line.chop(1);
    QStringList list_formuls = line.split(']');

    std::vector<SimpleFormulaElement> formula_for_single;

    for(auto it(list_formuls.cbegin()); it != list_formuls.cend(); it++)
    {
        auto temp_elements = subcalculate_subline(*it);
        formula_for_single.insert(formula_for_single.cend(), temp_elements.cbegin(), temp_elements.cend());
    }

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
        if(dt_sld->getElement(it.symbol(), it.nucleons()).is_empty())
            return false;

    return true;
}







