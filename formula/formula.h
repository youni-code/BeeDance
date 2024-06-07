#ifndef FORMULA_H
#define FORMULA_H
#include <QString>
#include "chemicalformulaelement.h"
// #include "element.h"
#include "subformula.h"
#include "datatablesld.h"





class Formula
{

private:
    DataTableSLD dt_sld;

    bool is_root() { return current == root; }

    bool move_to_parent();
    bool add_child();

    SubFormula *root;
    SubFormula *current;

    std::vector<SubFormula*> subformulas;
    std::vector<double> squarebrackets_index;


    bool add_element(QString);
    bool close_bracket(QString);
    bool open_bracket(QString);
    bool square_brackets(QString);


    QString remove_int_value(QString &str);
    QString remove_element_name(QString &str);
    QString remove_double_index(QString &str);

    QString remove_element(QString &str);
    QString remove_open_bracket(QString &str);
    QString remove_close_bracket_index(QString &str);
    QString remove_square_brackets(QString &str);

    void clear();
public:

    bool is_correct(QString str);

    Formula() { current = root = new SubFormula(nullptr); }
    ~Formula() { clear(); delete root; }

    std::vector<ChemicalFormulaElement> get_elements(QString);

};


#endif // FORMULA_H
