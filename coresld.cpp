#include "coresld.h"

bool CoreSLD::is_line_correct()
{
    return formula.is_correct(str_formula);
}


void CoreSLD::set_formula(QString strformula)
{
    str_formula = strformula;
    calc_sld.set_elements(formula.get_elements(strformula));

}
void CoreSLD::set_density(double density)
{
    density_ = density;
    calc_sld.set_density(density_);
}

void CoreSLD::set_wavelength(double lambda)
{
    lambda_ = lambda;
    calc_sld.set_lambda(lambda);
}


















