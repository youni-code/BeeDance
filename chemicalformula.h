#ifndef CHEMICALFORMULA_H
#define CHEMICALFORMULA_H
#include <QString>
#include "simpleformulaelement.h"
#include "chemicalformulachecking.h"
// #include "calculation.h"


class ChemicalFormula
{


    std::vector<SimpleFormulaElement> vec;
    QString formula;
    ChemicalFormulaChecking cfch;

private:
    std::pair<QString::ConstIterator, QString::ConstIterator> brackets_index_inside(QString const &);
    std::pair<QString::ConstIterator, QString::ConstIterator> brackets_inside(QString const &);
    double get_index(QString const &);

    SimpleFormulaElement readIsotope(QString line = "");
    bool hasBrackets(QString line) const;
    bool hasSquareBrackets(QString line) const;

    QString getLine(QString::ConstIterator begin, QString::ConstIterator end);
    QString getLine(std::pair<QString::ConstIterator, QString::ConstIterator> p) { return getLine(p.first, p.second); }

    QString::ConstIterator it_on_SecondElement(const QString &line);
    SimpleFormulaElement get_firstElement(QString const line);
    QString del_firstElement(QString const line);


    std::vector<SimpleFormulaElement> getElements(QString);

    bool is_multiformula(QString);
    bool is_multiformula() { return is_multiformula(formula); };

public:
    ChemicalFormula(QString line = "");
    void setFormula(QString line);
    std::vector<SimpleFormulaElement> getElements();

    void multiple_by_index(std::vector<SimpleFormulaElement>& vec, double index);
    bool is_correct()
    {
        return cfch.is_correct();
    }
};

#endif // CHEMICALFORMULA_H
