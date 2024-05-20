#ifndef CORESLD_H
#define CORESLD_H

#include <QObject>
#include "calculationsld.h"
#include "formula.h"

class CoreSLD : public QObject
{
    // Q_OBJECT
private:
    Formula formula;

    double density_;
    double lambda_;
    QString str_formula;
    CalculationSLD calc_sld;

public:
    CoreSLD() { }
    bool is_correct() { return is_line_correct() && is_density_correct(); };

    bool is_line_correct();;
    bool is_density_correct() { return density_ > 0.0; }
    bool is_lambda_correct() { return lambda_ > 0.0; }

    void set_formula(QString formula);
    void set_density(double density);
    void set_wavelength(double density);

    bool valid_sld()            { return calc_sld.v_sld_re(); }
    double get_sld()            { return calc_sld.sld_re(); }
    double get_sld_err()        { return calc_sld.d_sld_re(); }

    bool valid_sld_im()         { return calc_sld.v_sld_im(); }
    double get_sld_im()         { return calc_sld.sld_im(); }
    double get_sld_im_err()     { return calc_sld.d_sld_im(); }

    bool valid_potv()           { return calc_sld.v_v_re(); }
    double get_potv()           { return calc_sld.v_re(); }
    double get_potv_err()       { return calc_sld.d_v_re(); }

    bool valid_potv_im()        { return calc_sld.v_v_im(); }
    double get_potv_im()        { return calc_sld.v_im(); }
    double get_potv_im_err()    { return calc_sld.d_v_im(); }

    bool valid_charact_wavelenght()         { return calc_sld.v_lambda_c(); }
    double get_charact_wavelength()         { return calc_sld.lambda_c(); }
    double get_charact_wavelength_error()   { return calc_sld.d_lambda_c(); }

    bool valid_critical_angle()             { return calc_sld.v_teta_c(); }
    double get_critical_angle()             { return calc_sld.tetta_c(); }
    double get_critical_angle_error()       { return calc_sld.d_tetta_c(); }

    bool valid_critical_momenutm()          { return calc_sld.v_q_c(); }
    double get_critical_momentum()          { return calc_sld.q_c(); }
    double get_critical_momentum_error()    { return calc_sld.d_q_c(); }

    bool valid_true_absorbtion()            { return calc_sld.v_mu_a(); }
    double get_true_absorbtion()            { return calc_sld.mu_a(); }
    double get_true_absorbtion_error()      { return calc_sld.d_mu_a(); }

    bool valid_incoherrent_scattering()         { return calc_sld.v_mu_i(); }
    double get_incoherrent_scattering()         { return calc_sld.mu_i(); }
    double get_incoherrent_scattering_error()   { return calc_sld.d_mu_i(); }

    bool valid_mu()         { return calc_sld.v_mu(); }
    double get_mu()         { return calc_sld.mu(); }
    double get_mu_error()   { return calc_sld.d_mu(); }

    bool valid_all()        { return calc_sld.valid_all(); }
};

#endif // CORESLD_H
