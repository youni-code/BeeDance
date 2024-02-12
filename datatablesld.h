#ifndef DATATABLESLD_H
#define DATATABLESLD_H
#include "element.h"
#include "readdatafiles.h"
#include <vector>
#include <map>

class DataTableSLD
{
    std::vector<Element> set_elements;
    std::map<QString, unsigned long> elemNum;

    void setData(std::vector<Element>);
    void setData(std::map<QString, unsigned long>);
public:
    DataTableSLD();
    void setReadData(ReadDataFiles*);
    Element getElement(QString const, unsigned long const = 0) const;
};

#endif // DATATABLESLD_H
