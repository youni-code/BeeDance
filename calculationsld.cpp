#include "calculationsld.h"

CalculationSLD::CalculationSLD() {}

double CalculationSLD::get_real_sld()
{
    double a_formula(0);
    double b_formula(0);

    for(auto &it : elements_)
    {
        auto elem = table_->getElement(it.symbol(), it.nucleons());

        a_formula += it.index() * elem.get_mass();
        b_formula += it.index() * elem.get_bc().real() * std::pow(10, -5);
    }

    return (density_ * b_formula) / (a_formula * 1.660153907);
}

double CalculationSLD::get_real_sld_error()
{

}
