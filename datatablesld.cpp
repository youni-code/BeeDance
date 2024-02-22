#include "datatablesld.h"


DataTableSLD::DataTableSLD() {}

void DataTableSLD::setReadData(ReadDataFiles *read)
{

    set_elements = read->getElements();
    elemNum = read->getMap();
}

Element DataTableSLD::getElement(const QString symb, const unsigned long nucl) const
{
    for(auto it = set_elements.cbegin(); it != set_elements.cend(); it++)
        if(it->getSymbol() == symb && it->get_countNucleons() == nucl)
            return (*it);
    return Element("", 0);
}
