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
    void setDensity(double density);
    void setLambda(double density);

    double get_sld() { return calc_sld->get_real_sld(); }
    double get_sld_err() { return calc_sld->get_real_sld_error(); }

    double get_potv() { return calc_sld->get_potential_v(); }
    double get_potv_err() { return calc_sld->get_potential_v_error(); }

    double get_charact_wavelength() { return calc_sld->get_characteristic_wavelength(); }
    double get_charact_wavelength_error() { return calc_sld->get_characteristic_wavelength_error(); }

    double get_critical_angle() { return calc_sld->get_critical_angle(); }
    double get_critical_angle_error() { return calc_sld->get_critical_angle_error(); }

    double get_critical_momentum() { return calc_sld->get_critical_momentum(); }

    double get_true_absorbtion() { return calc_sld->get_true_absorption(); }

    double get_incoherrent_scattering() { return calc_sld->get_incoh_scatt(); }

};

#endif // CORESLD_H
