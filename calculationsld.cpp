#include "calculationsld.h"
#include <QDebug>

double CalculationSLD::mod(std::complex<double> val) const
{
    return sqrt(val.real() * val.real() + val.imag() * val.imag());
}

std::complex<double> CalculationSLD::b(Element *elem) const
{
    return std::complex(elem->bc_comp().real(), - ((elem->sigma_a() * lambda_ / lambda_0 + elem->sigma_i()) * 1e2) / (2 * lambda_ * 1e5));
}

std::complex<double> CalculationSLD::delta_b(Element *elem) const
{
    double imag = - sqrt(pow(elem->sigma_a_err() * lambda_ / lambda_0, 2) + pow(elem->sigma_i_err(), 2)) * (1e2) / (2 * lambda_ * 1e5);
    return std::complex(elem->bc_comp_err().real(), imag);
}

double CalculationSLD::c_summ() const
{
    double sum(0.0);
    for(auto &it : elements_)
        sum += it.index();
    return sum;
}

double CalculationSLD::a_mass() const
{
    double mass(0);
    for(auto &it : elements_)
        mass += it.index() * it.element()->mass();
    return mass;
}

double CalculationSLD::sigma_a() const
{
    double sigma(0);
    for(auto &it : elements_)
        sigma += it.index() * it.element()->sigma_a();
    return sigma;
}

double CalculationSLD::delta_sigma_a() const
{
    double d_sigma(0);
    for(auto &it : elements_)
        d_sigma += it.index() * pow(it.element()->sigma_a_err(), 2);
    return sqrt(d_sigma);
}


double CalculationSLD::sigma_i() const
{
    double sigma(0);
    for(auto &it : elements_)
        sigma += it.index() * it.element()->sigma_i();
    return sigma;
}

double CalculationSLD::delta_sigma_i() const
{
    double sigma(0);
    for(auto &it : elements_)
        sigma += it.index() * pow(it.element()->sigma_i_err(), 2);
    return sqrt(sigma);
}


double CalculationSLD::sigma_t() const
{
    double result(0);
    for(auto &it : elements_)
    {
        auto comp = b(it.element());
        result +=  4 * pi * it.index() *(comp.imag() * comp.imag() + comp.real() * comp.real()) * 1e-2;
    }
    return result;
}

double CalculationSLD::delta_sigma_t() const
{
    double sub_result(0);
    for(auto &it : elements_)
    {
        auto delta_val = delta_b(it.element());
        auto val = b(it.element());
        sub_result +=  it.index() * pow(mod(val) * mod(delta_val), 2);
    }
    return 4 * pi * sqrt(sub_result) * 1e-2;

}

double CalculationSLD::sigma_c() const
{
    std::complex res(0);
    for(auto &it : elements_)
    {
        std::complex comp = b(it.element());
        res += it.index() * comp / c_summ();
    }
    return 4 * pi * (res.real() * res.real() + res.imag() * res.imag()) * 1e-2 * c_summ();
}

double CalculationSLD::delta_sigma_c() const
{
    std::complex<double> sub_res1(0);
    double sub_res2(0);

    for(auto &it : elements_)
    {
        sub_res1 += b(it.element());
        sub_res2 += it.index() * pow(mod(delta_b(it.element())), 2);
    }
    return 4 * pi * mod(sub_res1) * sqrt(sub_res2) * (1e-2 / c_summ());
}

double CalculationSLD::sigma_i_elem() const { return sigma_t() - sigma_c(); }
double CalculationSLD::delta_sigma_i_elem() const { return sqrt(pow(delta_sigma_t(), 2) + pow(delta_sigma_c(), 2)); }

double CalculationSLD::b_c() const
{
    double result(0);
    for(auto &it : elements_)
        result += it.index() * it.element()->bc_comp().real();
    return result;
}

double CalculationSLD::delta_b_c() const
{
    double result(0);
    for(auto &it : elements_)
        result += it.index() * pow(it.element()->bc_comp_err().real(), 2);
    return sqrt(result);
}

double CalculationSLD::b_a()        const { return (sigma_a() * (lambda_ / lambda_0) * 1e2) / (2 * lambda_ * 1e5); }
double CalculationSLD::delta_b_a()  const { return (delta_sigma_a() * (lambda_ / lambda_0) * 1e2) / (2 * lambda_ * 1e5); }

double CalculationSLD::b_i()        const { return ((sigma_i() + sigma_i_elem()) * 1e2) / (2 * lambda_ * 1e5); }
double CalculationSLD::delta_b_i()  const { return (sqrt(pow(delta_sigma_i(), 2) + pow(delta_sigma_i_elem(), 2)) * 1e2) / (2 * lambda_ * 1e5); }

double CalculationSLD::b_im()       const { return b_a() + b_i(); }
double CalculationSLD::delta_b_im() const { return sqrt(pow(delta_b_a(), 2) + pow(delta_b_i(), 2)); }


double CalculationSLD::sld()        const { return  c_sld * density_ / a_mass() * b_c(); }
double CalculationSLD::delta_sld()  const { return  c_sld * density_ / a_mass() * delta_b_c(); }


double CalculationSLD::sld_im()         const { return c_sld * density_ / a_mass() * b_im(); }
double CalculationSLD::delta_sld_im()   const { return c_sld * density_ / a_mass() * delta_b_im(); }


double CalculationSLD::v()          const { return c_sldV * sld(); }
double CalculationSLD::delta_v()    const { return c_sldV * delta_sld(); }


double CalculationSLD::v_im()       const { return c_sldV * sld_im(); }
double CalculationSLD::delta_v_im() const { return c_sldV * delta_sld_im(); }

double CalculationSLD::lambda_c() const
{
    if(v() > 0.0) return c_lambda / std::sqrt(v());
    return 0.0;
}

double CalculationSLD::delta_lambda_c() const
{
    if(v() > 0.0)
        return (lambda_c() / 2) * (delta_v() / v());
    return 0.0;
}

double CalculationSLD::teta_c() const
{
    if(lambda_c() > 0.0)
        return 1e3 / v();
    return 0.0;
}

double CalculationSLD::delta_teta_c() const
{
    if(lambda_c() > 0.0)
        return teta_c() * (delta_lambda_c() / lambda_c());
    return 0.0;
}

double CalculationSLD::q_c() const
{
    if(lambda_c() > 0.0) return 4 * pi / lambda_c();
    return 0.0;
}

double CalculationSLD::delta_q_c() const
{
    if(lambda_c() > 0.0)
        return q_c() * (delta_lambda_c() / lambda_c());
    return 0.0;
}

double CalculationSLD::mu_a() const       { return c_sigma_mu * density_ * sigma_a() / (a_mass()) * (lambda_ / lambda_0); }
double CalculationSLD::delta_mu_a() const { return c_sigma_mu * density_ * delta_sigma_a() / (a_mass()) * (lambda_ / lambda_0); }

double CalculationSLD::mu_i() const       { return c_sigma_mu * density_ * (sigma_i() + sigma_i_elem()) / a_mass(); }
double CalculationSLD::delta_mu_i() const { return c_sigma_mu * density_ * sqrt(pow(delta_sigma_i(), 2) + pow(delta_sigma_i_elem(), 2)) / a_mass(); }

double CalculationSLD::mu() const         { return mu_a() + mu_i(); }
double CalculationSLD::delta_mu() const   { return delta_mu_a() + delta_mu_i(); }


bool CalculationSLD::v_mass() const
{
    for(auto const &it : elements_)
        if(!it.element()->is_mass())
            return false;
    return true;
}

bool CalculationSLD::v_sigma_a() const
{
    for(auto const &it : elements_)
        if(!it.element()->is_sigma_a())
            return false;
    return true;
}

bool CalculationSLD::v_sigma_i() const
{
    for(auto const &it : elements_)
        if(!it.element()->is_sigma_i())
            return false;
    return true;
}

bool CalculationSLD::v_bc() const
{
    for(auto const &it : elements_)
        if(!it.element()->is_bc())
            return false;
    return true;
}

CalculationSLD::CalculationSLD()
{
}




