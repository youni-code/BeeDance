#ifndef CHEMICALFORMULA_H
#define CHEMICALFORMULA_H
#include <QString>
#include "simpleformulaelement.h"


class ChemicalFormula
{
private:
    std::vector<SimpleFormulaElement> vec;
    QString formula;


    QString::ConstIterator it_on_SecondElement(const QString &line);

    SimpleFormulaElement readIsotope(QString line = "");
    bool hasBrackets(QString line);
    QString getLine(QString::ConstIterator begin, QString::ConstIterator end);
    QString getLine(std::pair<QString::ConstIterator, QString::ConstIterator>);
    std::vector<SimpleFormulaElement> getElements(QString);

    std::pair<QString::ConstIterator, QString::ConstIterator> brackets_index_inside(QString const &);
    std::pair<QString::ConstIterator, QString::ConstIterator> brackets_inside(QString const &);
    double get_index(QString const &);

    void multiple_on_index(std::vector<SimpleFormulaElement>&, double);

public:
    ChemicalFormula(QString);
    void setFormula(QString const line) { formula = line; }
    std::vector<SimpleFormulaElement> getElements();
    SimpleFormulaElement get_firstElement(QString const line);
    QString del_firstElement(QString const line);
};

#endif // CHEMICALFORMULA_H
