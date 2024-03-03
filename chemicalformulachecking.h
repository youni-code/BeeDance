#ifndef CHEMICALFORMULACHECKING_H
#define CHEMICALFORMULACHECKING_H
#include <QRegularExpression>


class ChemicalFormulaChecking
{
    const static QRegularExpression open_brackets;
    const static QRegularExpression close_brackets;

    const static QRegularExpression re_element_format;
    const static QRegularExpression re_square_brackets;
    const static QRegularExpression re_square_brackets_end;
    const static QRegularExpression re_brackets;

    QString line_;

    bool has_brackets() const;
    bool check_format() const;
    bool check_brackets() const;
    bool check_sqbrackets() const;



public:
    ChemicalFormulaChecking(QString line = "") { set_line(line); };
    void set_line(QString line) { line_ = line; };
    bool is_correct() const;
};

const QRegularExpression ChemicalFormulaChecking::open_brackets =               QRegularExpression("[(]");
const QRegularExpression ChemicalFormulaChecking::close_brackets =              QRegularExpression("[)]");

const QRegularExpression ChemicalFormulaChecking::re_element_format =           QRegularExpression("([\\^][0-9]+)?[A-Z][a-z]*([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)?");
const QRegularExpression ChemicalFormulaChecking::re_square_brackets =          QRegularExpression("[\\[]([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)[\\]]");
const QRegularExpression ChemicalFormulaChecking::re_square_brackets_end =      QRegularExpression("[\\[]([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)[\\]]$");
const QRegularExpression ChemicalFormulaChecking::re_brackets =                 QRegularExpression("[(][)]([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)?");
#endif // CHEMICALFORMULACHECKING_H
