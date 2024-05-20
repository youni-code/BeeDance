#ifndef CALCULATIONSLD_H
#define CALCULATIONSLD_H

#include "chemicalformulaelement.h"

class CalculationSLD
{
    std::vector<ChemicalFormulaElement> elements_;
    double density_;
    double lambda_;

    static constexpr double lambda_0 = 1.798;
    static constexpr double pi = 3.14159265358979323846;
    static constexpr double h = 6.6260690e-34;
    static constexpr double m_a = 1.66053907e-24; // g/Da
    static constexpr double u_eV = 1.6021765e-19;
    static constexpr double m_n = 1.6749273e-27;
    static constexpr double v_ = 100;

    static constexpr double hcr = h / (2 * pi);
    static constexpr double c = (hcr * hcr / m_n) * 2 * pi; ;
    static constexpr double c_sldV = (c * 1e29) / (u_eV);
    static constexpr double c_sld = 1e-29 / m_a;
    static constexpr double c_sigma_mu = 1e-24 / m_a;
    const double c_lambda = ((h)/(u_eV * 1e-9) * 1e10) / std::sqrt(2 * (m_n)/(u_eV * 1e-9));

    double mod(std::complex<double>) const;

    std::complex<double> b(const Element&)        const;
    std::complex<double> delta_b(const Element&)  const;

    double c_summ() const;
    double a_mass() const;

    double sigma_a() const;
    double delta_sigma_a() const;
    double sigma_i() const;
    double delta_sigma_i() const;
    double sigma_t() const;
    double delta_sigma_t() const;
    double sigma_c() const;
    double delta_sigma_c() const;
    double sigma_i_elem() const;
    double delta_sigma_i_elem() const;

    double b_c() const;
    double delta_b_c() const;
    double b_a() const;
    double delta_b_a() const;
    double b_i() const;
    double delta_b_i() const;
    double b_im() const;
    double delta_b_im() const ;

    bool v_mass()       const;
    bool v_sigma_a()    const;
    bool v_sigma_i()    const;
    bool v_bc()         const;

public:
    CalculationSLD();

    void set_elements(std::vector<ChemicalFormulaElement> elements) { elements_ = elements; }
    void set_density(double density) { density_ = density; }
    void set_lambda(double lambda) { lambda_ = lambda; }

    bool v_sld_re()   const { return v_mass() && v_bc(); }
    bool v_sld_im()   const { return v_mass() && v_sigma_a() && v_sigma_i(); }
    bool v_v_re()     const { return v_mass() && v_bc(); }
    bool v_v_im()     const { return v_mass() && v_sigma_a() && v_sigma_i(); }
    bool v_lambda_c() const { return v_mass() && v_bc();  }
    bool v_teta_c()   const { return v_mass() && v_bc(); }
    bool v_q_c()      const { return v_mass() && v_bc(); }
    bool v_mu_a()     const { return v_mass() && v_sigma_a(); }
    bool v_mu_i()     const { return v_mass() && v_sigma_i(); }
    bool v_mu()       const { return v_mass() && v_sigma_a() && v_sigma_i(); }
    bool valid_all()  const { return v_mass() && v_sigma_a() && v_sigma_i() && v_bc(); }

    double sld_re() const;
    double d_sld_re() const;
    double sld_im() const;
    double d_sld_im() const;
    double v_re() const;
    double d_v_re() const;
    double v_im() const;
    double d_v_im() const;

    double lambda_c() const;
    double d_lambda_c() const;
    double tetta_c() const;
    double d_tetta_c() const;
    double q_c() const;
    double d_q_c() const;

    double mu_a() const;
    double d_mu_a() const;
    double mu_i() const;
    double d_mu_i() const;
    double mu() const;
    double d_mu() const;
};

#endif // CALCULATIONSLD_H
