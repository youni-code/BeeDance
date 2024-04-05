#include "calculationsld.h"

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

