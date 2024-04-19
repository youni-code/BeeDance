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
    const double v_ = 100;

    const double hcr = h / (2 * pi);
    const double c = (hcr * hcr / m_n) * 2 * pi; ;
    const double c_sldV = (c * 1e29) / (u_eV);
    const double c_sld = 1e-29 / m_a;
    const double c_lambda = ((h)/(u_eV * 1e-9) * 1e10) / std::sqrt(2 * (m_n)/(u_eV * 1e-9));
    const double lambda_c_ = c_lambda / std::sqrt(v_);
    const double teta_c_ = 1e3 / lambda_c_;
    const double q_c_ = 4 * pi / lambda_c_;
    const double c_sigma_mu = 1e-24 / m_a;

    std::complex<double> b(Element*);

    double c_summ();
    double a_mass();

    double sigma_a();
    double delta_sigma_a();

    double sigma_i();
    double delta_sigma_i();

    double sigma_t();
    double delta_sigma_t();

    double sigma_c();
    double delta_sigma_c();

    double sigma_i_elem();
    double delta_sigma_i_elem();

    double b_c();
    double delta_b_c();

    double b_a();
    double b_i();
    double b_im();

    double sld();
    double delta_sld();

    double sld_im();
    double delta_sld_im();

    double v();
    double delta_v();

    double lambda_c();
    double delta_lambda_c();

    double teta_c();
    double delta_teta_c();

    double q_c();
    double delta_q_c();

    double mu_a();
    double delta_mu_a();

    double mu_i();
    double delta_mu_i();

public:
    CalculationSLD();

    void set_elements(std::vector<ChemicalFormulaElement> elements) { elements_ = elements; }
    void set_density(double density) { density_ = density; }
    void set_lambda(double lambda) { lambda_ = lambda; }


    double get_real_sld() { return sld(); }
    double get_real_sld_error() { return delta_sld(); }

    double get_im_sld();
    double get_im_sld_error();

    double get_potential_v() { return v(); }
    double get_potential_v_error() { return delta_v(); }

    double get_characteristic_wavelength() { return lambda_c(); }
    double get_characteristic_wavelength_error() { return delta_lambda_c(); }

    double get_critical_angle() { return teta_c(); };
    double get_critical_angle_error() { return delta_teta_c(); };

    double get_critical_momentum() { return q_c(); };
    double get_critical_momentum_error() { return delta_q_c(); };

    double get_true_absorption() { return mu_a(); }
    double get_true_absorption_error() { return delta_mu_a(); }

    double get_incoh_scatt() { return mu_i(); }
};

#endif // CALCULATIONSLD_H
