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

    bool is_back() { return current != root; };
    bool is_root() { return current == root; }

    void move_to_parent();
    void add_child();

    SubFormula *root;
    SubFormula *current;

    std::vector<SubFormula*> subformulas;
    std::vector<double> squarebrackets_index;



    bool add_element(QString);
    void close_bracket(QString);
    void open_bracket(QString);
    void square_brackets(QString);



    QString remove_int_value(QString &str);
    QString remove_element_name(QString &str);
    QString remove_double_index(QString &str);

    QString remove_element(QString &str);
    QString remove_open_bracket(QString &str);
    QString remove_close_bracket_index(QString &str);
    QString remove_square_brackets(QString &str);

public:



    bool add_line(QString str);

    Formula();
    std::vector<ChemicalFormulaElement*> get_elements();

};


#endif // FORMULA_H
