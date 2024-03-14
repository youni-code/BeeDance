#ifndef CORESLD_H
#define CORESLD_H

// #include "readdatafiles.h"
#include "chemicalformula.h"
#include "datatablesld.h"
#include "chemicalformulaelement.h"
#include "calculationsld.h"

class CoreSLD : public QObject
{
    // Q_OBJECT
private:
    double density_;
    ChemicalFormula *chem_formula = nullptr;
    DataTableSLD *dt_sld = nullptr;
    QString str_formula;
    CalculationSLD *calc_sld = nullptr;

private:
    double full_mass(QString);

    double read_value_squarebrackets(QString);
    std::vector<SimpleFormulaElement> subcalculate_subline(QString);
    std::vector<ChemicalFormulaElement> to_chemical_formula_element(std::vector<SimpleFormulaElement>);

    std::vector<SimpleFormulaElement> multiformula_to_singleformula(QString);
    bool isMultiFormula(QString line) { return line.contains(']'); }

public:
    CoreSLD();
    bool is_correct() { return is_line_correct() && is_density_correct() && is_all_data_exist(); };

    bool is_line_correct() { return chem_formula->is_correct(); };
    bool is_density_correct() { return density_ > 0.0; };
    bool is_all_data_exist();

    void setFormula(QString formula);
    void setDensity(double density);;

    double get_sld();
    double get_sld_err();

};

#endif // CORESLD_H
