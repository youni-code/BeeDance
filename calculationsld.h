#ifndef CALCULATIONSLD_H
#define CALCULATIONSLD_H

#include "chemicalformulaelement.h"

class CalculationSLD
{
    std::vector<ChemicalFormulaElement> elements_;
    // DataTableSLD* table_;
    double density_;
    double lambda_;

    const double lambda_0 = 1.798;
    const double pi = 3.14159265358979323846;
    const double h = 6.6260690e-34;
    const double m_a = 1.66053907e-24; // g/Da
    const double u_eV = 1.6021765e-19;
    const double m_n = 1.6749273e-27;
    const double v = 100;

    const double hcr = h / (2 * pi);
    const double c = (hcr * hcr / m_n) * 2 * pi; ;
    const double c_sldV = (c * 1e29) / (u_eV);
    const double c_lambda = ((h)/(u_eV * 1e-9) * 1e10) / std::sqrt(2 * (m_n)/(u_eV * 1e-9));
    const double lambda_c = c_lambda / std::sqrt(v);
    const double teta_c = 1e3 / lambda_c;
    const double q_c = 4 * pi / lambda_c;

    std::complex<double> b(Element*);

    double c_summ();
    double sigma_a();
    double a_mass();
    double sigma_i();

    double sigma_t();
    double sigma_c();
    double sigma_i_elem();

    double b_a();
    double b_i();
    double b_im();

public:
    CalculationSLD();
    // void set_table(DataTableSLD* table) { table_ = table; }
    void set_elements(std::vector<ChemicalFormulaElement> elements) { elements_ = elements; }
    void set_density(double density) { density_ = density; }
    void set_lambda(double lambda) { lambda_ = lambda; }


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
