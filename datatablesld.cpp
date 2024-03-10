#include "readdatafiles.h"
#include "datatablesld.h"



DataTableSLD::DataTableSLD()
{
    auto read = new ReadDataFiles();
    set_elements = read->getElements();
    delete read;
}


Element DataTableSLD::getElement(const QString symb, const unsigned long nucl) const
{
    for(auto it = set_elements.cbegin(); it != set_elements.cend(); it++)
        if(it->get_symbol() == symb && it->get_countNucleons() == nucl)
            return (*it);
    return Element("", 0);
}

Element DataTableSLD::getElement(const SimpleFormulaElement &el) const
{
    return getElement(el.symbol(), el.nucleons());
}
