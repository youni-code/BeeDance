#ifndef CORESLD_H
#define CORESLD_H

// #include "readdatafiles.h"
#include "chemicalformula.h"
#include "datatablesld.h"
#include "chemicalformulaelement.h"
#include "calculationsld.h"

class CoreSLD : public QObject
{
    Q_OBJECT
private:
    double density_;
    ChemicalFormula *chem_formula = nullptr;
    DataTableSLD *dt_sld = nullptr;
    QString str_formula;
    CalculationSLD *calc_sld = nullptr;


    double full_mass(QString);

    double calculate_sld(QString);
    double calculate_sld_err(QString);

    double calculate_multisld(QString);
    double calculate_multisld_err();
    double calculate_multisld_err(QString);

    double calculate_singlesld() { return calc_sld->get_real_sld(); }

    double calculate_singlesld_err(QString);
    double calculate_singlesld_err(std::vector<SimpleFormulaElement>);

    bool isMultiFormula(QString line) { return line.contains(']'); }
    double read_value_squarebrackets(QString);
    std::vector<SimpleFormulaElement> subcalculate_subline(QString);
    QString delete_squarebrackets(QString);

    std::vector<ChemicalFormulaElement> to_chemical_formula_element(std::vector<SimpleFormulaElement>);
    std::vector<ChemicalFormulaElement> to_chemical_formula_element();

    std::vector<SimpleFormulaElement> multiformula_to_singleformula(QString);



public:
    CoreSLD();
    bool is_correct() { return is_line_correct() && is_density_correct() && is_all_data_exist(); };

    bool is_line_correct() { return chem_formula->is_correct(); };
    bool is_density_correct() { return density_ > 0.0; };
    bool is_all_data_exist();

    void setFormula(QString formula) { chem_formula->setFormula(str_formula = formula); }
    void setDensity(double density) { density_ = density; };

    double get_sld() { return calculate_sld(str_formula); }
    double get_sld_err() { return calculate_singlesld_err(str_formula); }

};

#endif // CORESLD_H
