#include "calculationsld.h"
#include <QDebug>


std::complex<double> CalculationSLD::b(Element *elem)
{
    double real = elem->bc().real();
    double imag = - ((elem->sigma_a() * lambda_ / lambda_0 + elem->sigma_i()) * 1e2) / (2 * lambda_ * 1e5);

    return std::complex(real, imag);
}

double CalculationSLD::c_summ()
{
    double sum(0.0);
    for(auto &it : elements_) sum += it.index();
    return sum;
}

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

double CalculationSLD::a_mass()
{
    double mass(0);
    for(auto &it : elements_) mass += it.index() * it.element()->mass();

    return mass;
}

double CalculationSLD::sigma_i()
{
    double sigma(0);
    for(auto &it : elements_) sigma += it.index() * it.element()->sigma_i();

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

double CalculationSLD::sigma_c()
{
    std::complex res(0);
    for(auto &it : elements_)
    {
        std::complex comp = b(it.element());
        res += it.index() * comp / c_summ();
    }
    double sigma = 4 * pi * (res.real() * res.real() + res.imag() * res.imag()) * 1e-2 * c_summ();
    return sigma;
}

double CalculationSLD::sigma_i_elem()
{
    return sigma_t() - sigma_c();
}

double CalculationSLD::delta_sigma_i_elem()
{
}

double CalculationSLD::b_c()
{
    double result(0);
    for(auto &it : elements_) result += it.index() * it.element()->bc().real();

    return result;
}

double CalculationSLD::delta_b_c()
{
    double result(0);
    for(auto &it : elements_) result += it.index() * pow(it.element()->bc_err().real(), 2);

    return sqrt(result);
}

double CalculationSLD::b_a()
{
    return (sigma_a() * (lambda_ / lambda_0) * 1e2) / (2 * lambda_ * 1e5);
}

double CalculationSLD::b_i()
{
    return ((sigma_i() + sigma_i_elem()) * 1e2) / (2 * lambda_ * 1e5);
}

double CalculationSLD::b_im()
{
    return b_a() + b_i();
}

double CalculationSLD::sld()
{
    return  c_sld * density_ / a_mass() * b_c();
}

double CalculationSLD::delta_sld()
{
    qDebug() << "delta: " << delta_b_c();
    return  c_sld * density_ / a_mass() * delta_b_c();
}

double CalculationSLD::v()
{
    return c_sldV * sld();
}

double CalculationSLD::delta_v()
{
    return c_sldV * delta_sld();
}

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
    if(lambda_c() > 0.0) return 1e3 / v();
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

double CalculationSLD::mu_a()
{
    return c_sigma_mu * density_ * sigma_a() / (a_mass()) * (lambda_ / lambda_0);
}

double CalculationSLD::delta_mu_a()
{
    return c_sigma_mu * density_ * delta_sigma_a() / (a_mass()) * (lambda_ / lambda_0);
}

double CalculationSLD::mu_i()
{
    qDebug() << "sigma i: " << sigma_i();
    qDebug() << "sigma i element: " << sigma_i_elem();
    return c_sigma_mu * density_ * (sigma_i() + sigma_i_elem()) / a_mass();
}

double CalculationSLD::delta_mu_i()
{
    // double brackets = sqrt(pow(delta_sigma_i(), 2) + pow(delta_sigma_i_elem(), 2));
    // return c_sigma_mu * density_ / a_mass() * brackets;
}

CalculationSLD::CalculationSLD() {}











