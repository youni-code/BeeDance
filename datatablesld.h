#ifndef DATATABLESLD_H
#define DATATABLESLD_H
#include "element.h"
#include <vector>
#include <QStringList>

class DataTableSLD
{
    std::vector<Element> elements;


    void read_data();
    void save_data(QStringList);

public:
    DataTableSLD();
    Element get_element(QString, unsigned long = 0) const;
};

#endif // DATATABLESLD_H
