#include "calculationsld.h"

CalculationSLD::CalculationSLD() {}

double CalculationSLD::get_real_sld()
{
    double a_formula(0);
    double b_formula(0);

    for(auto &it : elements_)
    {
        qDebug() << it.element()->get_symbol() << " : " << it.element()->get_countNucleons() << ", mass: " << it.element()->get_mass();
        a_formula += it.index() * it.element()->get_mass();
        b_formula += it.index() * it.element()->get_bc().real() * std::pow(10, -5);
    }

    return (density_ * b_formula) / (a_formula * 1.660153907);
}

double CalculationSLD::get_real_sld_error()
{
    double a_formula(0);
    double b_formula(0);

    for(auto &it : elements_)
    {
        a_formula += it.index() * it.element()->get_mass();
        double sq_b = it.index() * it.element()->get_bc_error().real() * std::pow(10, -5);
        b_formula += sq_b * sq_b;
    }
    return (density_ * std::pow(b_formula, 0.5)) / (a_formula * 1.660153907);
}
