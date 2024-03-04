#include "chemicalformulachecking.h"
#include <stack>


bool ChemicalFormulaChecking::has_square_brackets() const
{
    return line_.contains(re_square_brackets);
}

bool ChemicalFormulaChecking::check_format() const
{
    auto line = line_;

    if(!line.contains(re_element_format)) return false;

    line = line.remove(re_square_brackets);
    line = line.remove(re_element_format);
    line = line.remove(re_brackets);

    qDebug() << "error here: " << line;
    if(line.isEmpty()) return true;
    return false;
}

bool ChemicalFormulaChecking::check_brackets() const
{
    auto &line = line_;

    std::stack<QChar> b_stack;

    for(auto it(line.cbegin()); it != line.cend(); it++)
    {
        if(QString(*it).contains(open_brackets))
            b_stack.push(*it);

        if(QString(*it).contains(close_brackets))
        {
            if(b_stack.empty())
                return false;

            if(QString(b_stack.top()).contains(open_brackets))
                b_stack.pop();
            else
                return false;
        }
    }
    return b_stack.empty();
}

bool ChemicalFormulaChecking::check_sqbrackets() const
{
    if(!has_square_brackets()) return true;
    return line_.contains(re_square_brackets_end);
}


ChemicalFormulaChecking::ChemicalFormulaChecking(QString line)
{
    set_line(line);
    open_brackets =               QRegularExpression("[(]");
    close_brackets =              QRegularExpression("[)]");

    re_element_format =           QRegularExpression("([\\^][0-9]+)?[A-Z][a-z]*([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)?");
    re_square_brackets =          QRegularExpression("[\\[]([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)[\\]]");
    re_square_brackets_end =      QRegularExpression("[\\[]([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)[\\]]$");
    re_brackets =                 QRegularExpression("[(][)]([0-9]+[.]?[0-9]*|[0-9]*[.][0-9]+)?");
}

bool ChemicalFormulaChecking::is_correct() const
{
    return check_format() && check_brackets() && check_sqbrackets();
}
