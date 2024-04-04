#ifndef CALCULATIONSLD_H
#define CALCULATIONSLD_H
// #include "datatablesld.h"
#include "chemicalformulaelement.h"

class CalculationSLD
{
    std::vector<ChemicalFormulaElement> elements_;
    // DataTableSLD* table_;
    double density_;

    double m_a = 1.66053907e-24; // g/Da

public:
    CalculationSLD();
    // void set_table(DataTableSLD* table) { table_ = table; }
    void set_elements(std::vector<ChemicalFormulaElement> elements) { elements_ = elements; }
    void set_density(double density) { density_ = density; }


    double get_real_sld();
    double get_real_sld_error();

    double get_im_sld();
    double get_im_sld_error();

    double get_potential_v();
    double get_characteristic_wavelength();
    double get_critical_angle();
    double get_critical_momentum();
};

#endif // CALCULATIONSLD_H
