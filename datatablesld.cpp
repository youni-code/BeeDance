#include "readdatafiles.h"
#include "datatablesld.h"



DataTableSLD::DataTableSLD()
{
    auto read = new ReadDataFiles();
    set_elements = read->getElements();
}

Element DataTableSLD::getElement(const QString symb, const unsigned long nucl) const
{
    for(auto it = set_elements.cbegin(); it != set_elements.cend(); it++)
        if(it->symbol() == symb && it->nucleons() == nucl)
            return (*it);
    return Element("", 0);
}

Element DataTableSLD::getElement(const SimpleFormulaElement &el) const
{
    qDebug() << "simpleformulaelement: " << el.symbol() << "nucleons: " << el.nucleons();
    return getElement(el.symbol(), el.nucleons());
}
