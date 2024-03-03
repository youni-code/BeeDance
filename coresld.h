#ifndef CORESLD_H
#define CORESLD_H

// #include "readdatafiles.h"
#include "chemicalformula.h"
#include "datatablesld.h"

class CoreSLD
{
private:
    double density_;
    ChemicalFormula *chem_formula = nullptr;
    DataTableSLD *dt_sld;
    QString str_formula;


    double full_mass(QString);

    double calculate_sld(QString);
    double calculate_multisld(QString);
    double calculate_singlesld(QString);
    double calculate_singlesld(std::vector<SimpleFormulaElement> elem_vec);
    bool isMultiFormula(QString);
    double read_value_squarebrackets(QString);
    std::vector<SimpleFormulaElement> subcalculate_subline(QString);
    QString delete_squarebrackets(QString);


signals:


public:
    CoreSLD();
    void setFormula(QString);
    void setDensity(double density) { density_ = density; };
    double get_sld();
    double get_sld(QString line);

};

#endif // CORESLD_H
