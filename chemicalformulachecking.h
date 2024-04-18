#ifndef CHEMICALFORMULACHECKING_H
#define CHEMICALFORMULACHECKING_H
#include <QRegularExpression>

class ChemicalFormulaChecking
{
    QRegularExpression open_brackets;
    QRegularExpression close_brackets;

    QRegularExpression re_element_format;
    QRegularExpression re_square_brackets;
    QRegularExpression re_square_brackets_end;
    QRegularExpression re_brackets;

    QString line_;


public:
    bool has_square_brackets() const;
    bool check_format() const;
    bool check_brackets() const;
    bool check_sqbrackets() const;

    ChemicalFormulaChecking(QString line = "");
    void set_line(QString line) { line_ = line; };
    bool is_correct() const;
};

#endif // CHEMICALFORMULACHECKING_H
