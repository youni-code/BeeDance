#ifndef DATATABLESLD_H
#define DATATABLESLD_H
#include "element.h"
#include <vector>
#include "simpleformulaelement.h"

class DataTableSLD
{
    std::vector<Element> set_elements;

    void setData(std::vector<Element>);
public:
    DataTableSLD();
    Element getElement(QString, unsigned long = 0) const;
    Element getElement(const SimpleFormulaElement&) const;
};

#endif // DATATABLESLD_H
