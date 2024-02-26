#ifndef DATATABLESLD_H
#define DATATABLESLD_H
#include "element.h"
#include <vector>

class DataTableSLD
{
    std::vector<Element> set_elements;

    void setData(std::vector<Element>);
public:
    DataTableSLD();
    Element getElement(QString const, unsigned long const = 0) const;
};

#endif // DATATABLESLD_H
