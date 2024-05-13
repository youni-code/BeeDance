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

    std::complex<double> b(Element*)        const;
    std::complex<double> delta_b(Element*)  const;

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

    double sld() const;
    double delta_sld() const;
    double sld_im() const;
    double delta_sld_im() const;
    double v() const;
    double delta_v() const;
    double v_im() const;
    double delta_v_im() const;

    double lambda_c() const;
    double delta_lambda_c() const;
    double teta_c() const;
    double delta_teta_c() const;
    double q_c() const;
    double delta_q_c() const;

    double mu_a() const;
    double delta_mu_a() const;
    double mu_i() const;
    double delta_mu_i() const;
    double mu() const;
    double delta_mu() const;



    bool v_mass()       const;
    bool v_sigma_a()    const;
    bool v_sigma_i()    const;
    bool v_bc()         const;


public:
    CalculationSLD();

    void set_elements(std::vector<ChemicalFormulaElement> elements) { elements_ = elements; }
    void set_density(double density) { density_ = density; }
    void set_lambda(double lambda) { lambda_ = lambda; }


    bool valid_real_sld()       const { return v_mass() && v_bc(); }
    double get_real_sld()       const { return sld(); }
    double get_real_sld_error() const { return delta_sld(); }

    bool valid_im_sld()         const { return v_sigma_a() && v_sigma_i() && v_mass(); }
    double get_im_sld()         const { return sld_im(); }
    double get_im_sld_error()   const { return delta_sld_im(); }

    bool valid_v()                  const { return v_mass() && v_bc(); }
    double get_potential_v()        const { return v(); }
    double get_potential_v_error()  const { return delta_v(); }

    bool valid_im_potential_v()         const { return v_mass() && v_sigma_a() && v_sigma_i(); }
    double get_im_potential_v()         const { return v_im(); }
    double get_im_potential_v_error()   const { return delta_v_im(); }

    bool valid_characteristic_wavelength()          const { return v_mass() && v_bc();  }
    double get_characteristic_wavelength()          const { return lambda_c(); }
    double get_characteristic_wavelength_error()    const { return delta_lambda_c(); }

    bool valid_critical_angle()         const { return v_mass() && v_bc(); }
    double get_critical_angle()         const { return teta_c(); };
    double get_critical_angle_error()   const { return delta_teta_c(); };

    bool valid_critical_momentum()          const { return v_mass() && v_bc(); }
    double get_critical_momentum()          const { return q_c(); };
    double get_critical_momentum_error()    const { return delta_q_c(); };

    bool valid_true_absorption()        const { return v_mass() && v_sigma_a(); }
    double get_true_absorption()        const { return mu_a(); }
    double get_true_absorption_error()  const { return delta_mu_a(); }

    bool valid_incoh_scatt()        const { return v_mass() && v_sigma_i(); }
    double get_incoh_scatt()        const { return mu_i(); }
    double get_incoh_scatt_error()  const { return delta_mu_i(); }

    bool valid_mu()         const { return v_mass() && v_sigma_a() && v_sigma_i(); }
    double get_mu()         const { return mu(); }
    double get_mu_error()   const { return delta_mu(); }

    bool valid_all()        const { return v_mass() && v_sigma_a() && v_sigma_i() && v_bc(); }
};

#endif // CALCULATIONSLD_H
