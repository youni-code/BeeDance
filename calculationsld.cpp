#include "calculationsld.h"
#include <QDebug>

double CalculationSLD::mod(std::complex<double> val) { return sqrt(val.real() * val.real() + val.imag() * val.imag()); }

std::complex<double> CalculationSLD::b(Element *elem) { return std::complex(elem->bc_comp().real(), - ((elem->sigma_a() * lambda_ / lambda_0 + elem->sigma_i()) * 1e2) / (2 * lambda_ * 1e5)); }

std::complex<double> CalculationSLD::delta_b(Element *elem)
{
    double imag = - sqrt(pow(elem->sigma_a_err() * lambda_ / lambda_0, 2) + pow(elem->sigma_i_err(), 2)) * (1e2) / (2 * lambda_ * 1e5);
    return std::complex(elem->bc_comp_err().real(), imag);
}

double CalculationSLD::c_summ()
{
    double sum(0.0);
    for(auto &it : elements_)
        sum += it.index();
    return sum;
}

double CalculationSLD::a_mass()
{
    double mass(0);
    for(auto &it : elements_)
        mass += it.index() * it.element()->mass();
    return mass;
}


// bool CalculationSLD::valid_a_mass()
// {
//     for(auto &it : elements_)
//         if(!it.element()->is_mass())
//             return false;
//     return true;
// }

double CalculationSLD::sigma_a()
{
    double sigma(0);
    for(auto &it : elements_)
        sigma += it.index() * it.element()->sigma_a();
    return sigma;
}

double CalculationSLD::delta_sigma_a()
{
    double d_sigma(0);
    for(auto &it : elements_)
        d_sigma += it.index() * pow(it.element()->sigma_a_err(), 2);
    return sqrt(d_sigma);
}


double CalculationSLD::sigma_i()
{
    double sigma(0);
    for(auto &it : elements_)
        sigma += it.index() * it.element()->sigma_i();
    return sigma;
}

double CalculationSLD::delta_sigma_i()
{
    double sigma(0);
    for(auto &it : elements_)
        sigma += it.index() * pow(it.element()->sigma_i_err(), 2);
    return sqrt(sigma);
}


double CalculationSLD::sigma_t()
{
    double result(0);
    for(auto &it : elements_)
    {
        auto comp = b(it.element());
        result +=  4 * pi * it.index() *(comp.imag() * comp.imag() + comp.real() * comp.real()) * 1e-2;
    }
    return result;
}

double CalculationSLD::delta_sigma_t()
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

double CalculationSLD::sigma_c()
{
    std::complex res(0);
    for(auto &it : elements_)
    {
        std::complex comp = b(it.element());
        res += it.index() * comp / c_summ();
    }
    return 4 * pi * (res.real() * res.real() + res.imag() * res.imag()) * 1e-2 * c_summ();
}

double CalculationSLD::delta_sigma_c()
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

double CalculationSLD::sigma_i_elem()       { return sigma_t() - sigma_c(); }
double CalculationSLD::delta_sigma_i_elem() { return sqrt(pow(delta_sigma_t(), 2) + pow(delta_sigma_c(), 2)); }

double CalculationSLD::b_c()
{
    double result(0);
    for(auto &it : elements_)
        result += it.index() * it.element()->bc_comp().real();
    return result;
}

double CalculationSLD::delta_b_c()
{
    double result(0);
    for(auto &it : elements_) result += it.index() * pow(it.element()->bc_comp_err().real(), 2);

    return sqrt(result);
}

double CalculationSLD::b_a()        { return (sigma_a() * (lambda_ / lambda_0) * 1e2) / (2 * lambda_ * 1e5); }
double CalculationSLD::delta_b_a()  { return (delta_sigma_a() * (lambda_ / lambda_0) * 1e2) / (2 * lambda_ * 1e5); }

double CalculationSLD::b_i()        { return ((sigma_i() + sigma_i_elem()) * 1e2) / (2 * lambda_ * 1e5); }
double CalculationSLD::delta_b_i()  { return (sqrt(pow(delta_sigma_i(), 2) + pow(delta_sigma_i_elem(), 2)) * 1e2) / (2 * lambda_ * 1e5); }

double CalculationSLD::b_im()       { return b_a() + b_i(); }
double CalculationSLD::delta_b_im() { return sqrt(pow(delta_b_a(), 2) + pow(delta_b_i(), 2)); }

bool CalculationSLD::valid_sld()
{
    for(auto &it : elements_)
    {
        if(!it.element()->is_mass()) return false;
        if(!it.element()->is_bc()) return false;
    }
    return true;
}

double CalculationSLD::sld()        { return  c_sld * density_ / a_mass() * b_c(); }
double CalculationSLD::delta_sld()  { return  c_sld * density_ / a_mass() * delta_b_c(); }

bool CalculationSLD::valid_sld_im()
{
    for(auto &it : elements_)
    {
        if(!it.element()->is_mass())    return false;
        if(!it.element()->is_sigma_a()) return false;
        if(!it.element()->is_sigma_i()) return false;
    }
    return true;
}

double CalculationSLD::sld_im()         { return c_sld * density_ / a_mass() * b_im(); }
double CalculationSLD::delta_sld_im()   { return c_sld * density_ / a_mass() * delta_b_im(); }

bool CalculationSLD::valid_v()
{
    for(auto &it : elements_)
    {
        if(!it.element()->is_mass())    return false;
        if(!it.element()->is_bc()) return false;
    }
    return true;
}

double CalculationSLD::v()          { return c_sldV * sld(); }
double CalculationSLD::delta_v()    { return c_sldV * delta_sld(); }

bool CalculationSLD::valid_v_im()
{
    for(auto &it : elements_)
    {
        if(!it.element()->is_mass())    return false;
        if(!it.element()->is_sigma_a()) return false;
        if(!it.element()->is_sigma_i()) return false;
    }
    return true;
}

double CalculationSLD::v_im()       { return c_sldV * sld_im(); }
double CalculationSLD::delta_v_im() { return c_sldV * delta_sld_im(); }

double CalculationSLD::lambda_c()
{
    if(v() > 0.0) return c_lambda / std::sqrt(v());
    return 0.0;
}

double CalculationSLD::delta_lambda_c()
{
    if(v() > 0.0)
        return (lambda_c() / 2) * (delta_v() / v());
    return 0.0;
}

double CalculationSLD::teta_c()
{
    if(lambda_c() > 0.0)
        return 1e3 / v();
    return 0.0;
}

double CalculationSLD::delta_teta_c()
{
    if(lambda_c() > 0.0)
        return teta_c() * (delta_lambda_c() / lambda_c());
    return 0.0;
}

double CalculationSLD::q_c()
{
    if(lambda_c() > 0.0) return 4 * pi / lambda_c();
    return 0.0;
}

double CalculationSLD::delta_q_c()
{
    if(lambda_c() > 0.0)
        return q_c() * (delta_lambda_c() / lambda_c());
    return 0.0;
}

double CalculationSLD::mu_a()       { return c_sigma_mu * density_ * sigma_a() / (a_mass()) * (lambda_ / lambda_0); }
double CalculationSLD::delta_mu_a() { return c_sigma_mu * density_ * delta_sigma_a() / (a_mass()) * (lambda_ / lambda_0); }

double CalculationSLD::mu_i()       { return c_sigma_mu * density_ * (sigma_i() + sigma_i_elem()) / a_mass(); }
double CalculationSLD::delta_mu_i() { return c_sigma_mu * density_ * sqrt(pow(delta_sigma_i(), 2) + pow(delta_sigma_i_elem(), 2)) / a_mass(); }

double CalculationSLD::mu()         { return mu_a() + mu_i(); }
double CalculationSLD::delta_mu()   { return delta_mu_a() + delta_mu_i(); }

CalculationSLD::CalculationSLD() {}

bool CalculationSLD::valid_real_sld()
{
    for(auto &it : elements_)
    {
        if(!it.element()->is_mass()) return false;
        if(!it.element()->is_bc()) return false;
    }
    return true;
}

bool CalculationSLD::valid_im_sld()
{
    for(auto &it : elements_)
    {
        if(!it.element()->is_bi())      return false;
        if(!it.element()->is_sigma_a()) return false;
        if(!it.element()->is_sigma_i()) return false;
        if(!it.element()->is_mass())    return false;
    }
    return true;

}
