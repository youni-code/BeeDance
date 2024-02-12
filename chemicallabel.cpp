#include "chemicallabel.h"

ChemicalLabel::ChemicalLabel() {}

void ChemicalLabel::setFormula(QString line)
{
    QString newline;
    for(auto it(line.cbegin()); it != line.cend(); it++)
    {
        if((*it) == '^') continue;
        newline.append(*it);
    }

    this->setText(newline);
}
