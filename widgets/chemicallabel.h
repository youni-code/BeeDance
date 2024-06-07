#ifndef CHEMICALLABEL_H
#define CHEMICALLABEL_H

#include <QLabel>
#include <QObject>

class ChemicalLabel : public QLabel
{
    Q_OBJECT
public:
    ChemicalLabel();
public slots:
    void setFormula(QString line);
};

#endif // CHEMICALLABEL_H
