#ifndef CHEMICALFORMULA_H
#define CHEMICALFORMULA_H
#include <QString>
#include "simpleformulaelement.h"
#include "chemicalformulachecking.h"


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

    ChemicalFormula(QString = "");
    void setFormula(QString line) { formula = line; vec = getElements(line); cfch.set_line(line); }
    std::vector<SimpleFormulaElement> getElements() { return getElements(formula); }


    void multiple_by_index(std::vector<SimpleFormulaElement>& vec, double index) { for(auto it(vec.begin()); it != vec.end(); it++) it->mult(index); }

    bool is_correct();
};

#endif // CHEMICALFORMULA_H
