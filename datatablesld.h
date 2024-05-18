#ifndef DATATABLESLD_H
#define DATATABLESLD_H
#include "element.h"
#include <vector>
#include "simpleformulaelement.h"

class DataTableSLD
{
    std::vector<Element> elements;

    void setData(std::vector<Element>);
public:
    DataTableSLD();
    Element get_element(QString, unsigned long = 0) const;
    Element get_element(const SimpleFormulaElement&) const;
};

#endif // DATATABLESLD_H
