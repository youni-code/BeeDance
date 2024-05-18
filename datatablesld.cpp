#include "readdatafiles.h"
#include "datatablesld.h"



DataTableSLD::DataTableSLD()
{
    ReadDataFiles read1;
    elements = read1.get_elements();
}

Element DataTableSLD::get_element(const QString symb, const unsigned long nucl) const
{
    // for (auto &it : set_elements);

    for(auto &it : elements)
        if(it.symbol() == symb && it.nucleons() == nucl)
            return it;
    return Element("", 0);
}

Element DataTableSLD::get_element(const SimpleFormulaElement &el) const
{
    return get_element(el.symbol(), el.nucleons());
}
