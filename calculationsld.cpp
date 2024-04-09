#include "calculationsld.h"


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

double CalculationSLD::a_mass()
{
    double mass(0);
    for(auto &it : elements_)
        mass += it.index() * it.element()->mass();
    return mass;
}

double CalculationSLD::sigma_i()
{
    double sigma(0);
    for(auto &it : elements_)
        sigma += it.index() * it.element()->sigma_i();
    return sigma;
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

CalculationSLD::CalculationSLD() {}

double CalculationSLD::get_real_sld()
{
    double a_formula(0);
    double b_formula(0);

    for(auto &it : elements_)
    {
        a_formula += it.index() * it.element()->mass();
        b_formula += it.index() * it.element()->bc().real();// * std::pow(10, -5);
    }

    return (density_ * b_formula) / (a_formula * 1.660153907) * std::pow(10, -5);
}

double CalculationSLD::get_real_sld_error()
{
    double a_formula(0);
    double b_formula(0);
    for(auto &it : elements_)
    {
        qDebug() << it.element()->symbol() << ": " << it.index();
    }

    for(auto &it : elements_)
    {
        a_formula += it.index() * it.element()->mass();
        double sq_b = it.index() * it.element()->bc_err().real();
        b_formula += sq_b * sq_b;
    }
    return (density_ * std::pow(b_formula, 0.5)) / (a_formula * 1.660153907) * std::pow(10, -5);
}

double CalculationSLD::get_potential_v()
{
    qDebug() << c_sldV;
    qDebug() << c_lambda;
    return c_sldV * get_real_sld();
}

