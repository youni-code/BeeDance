#ifndef CHEMICALFORMULA_H
#define CHEMICALFORMULA_H
#include <QString>
#include "simpleformulaelement.h"
// #include "chemicalformulachecking.h"


class ChemicalFormula
{
private:
    // ChemicalFormulaChecking cfch;

    std::vector<SimpleFormulaElement> vec;
    QString formula;

    QString getLine(QString::ConstIterator begin, QString::ConstIterator end);
    QString getLine(std::pair<QString::ConstIterator, QString::ConstIterator> p) { return getLine(p.first, p.second); }

    QString::ConstIterator it_on_SecondElement(const QString &line);
    SimpleFormulaElement get_firstElement(QString const line);
    QString del_firstElement(QString const line);

    std::pair<QString::ConstIterator, QString::ConstIterator> brackets_index_inside(QString const &);
    std::pair<QString::ConstIterator, QString::ConstIterator> brackets_inside(QString const &);
    double get_index(QString const &);

    SimpleFormulaElement readIsotope(QString line = "");
    bool hasBrackets(QString line) const;
    bool hasSquareBrackets(QString line) const;
    std::vector<SimpleFormulaElement> getElements(QString);

    bool is_multiformula(QString);
    bool is_multiformula() { return is_multiformula(formula); };


    bool check_roundbrackets(QString) const;
    bool check_roundbrackets() const { return check_roundbrackets(formula); };

    bool check_format(QString) const;
    bool check_format() const { return check_format(formula); }

    bool check_sqbrackets(QString) const;
    bool check_sqbrackets() const { return check_sqbrackets(formula); };

    bool is_correct(QString);

public:

    ChemicalFormula(QString = "");
    void setFormula(QString line) { formula = line; vec = getElements(line); }
    std::vector<SimpleFormulaElement> getElements();


    void multiple_by_index(std::vector<SimpleFormulaElement>& vec, double index) { for(auto it(vec.begin()); it != vec.end(); it++) it->mult(index); }

    bool is_correct();
};

#endif // CHEMICALFORMULA_H
