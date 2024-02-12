#ifndef SIMPLEELEMENT_H
#define SIMPLEELEMENT_H
#include <QString>
#include <QDebug>


class SimpleFormulaElement
{
private:
    QString symbol_;
    unsigned long nucleons_;
    double index_;
public:
    SimpleFormulaElement(QString const, unsigned long const = 0, double ind = 0.0);
    bool isIsotope() { return nucleons_ > 0; };
    bool isElement() { return nucleons_ == 0; };

    QString symbol() const { return symbol_; };
    unsigned long nucleons() const { return nucleons_; };
    double index() const { return index_; };

    void setindex(double val) { index_ = val; }
    void plus(double val) {index_ += val;};
    void mult(double val) { index_ *= val; };

    bool operator==(const SimpleFormulaElement&) const;
    bool operator!=(const SimpleFormulaElement&) const;
    bool operator<(SimpleFormulaElement&);
};

#endif // SIMPLEELEMENT_H
