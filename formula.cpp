#include "formula.h"

bool Formula::add_element(QString str)
{
    QString nucl;
    QString elem;
    QString index;

    int     real_nucl;
    QString real_elem;
    double  real_index;

    if(str.at(0) == '^')
        str.remove(0, 1); // if the first element is ^ - remove it.

    QString::ConstIterator it = str.cbegin();


    for(; it->isDigit() && it != str.cend(); it++)
        nucl.push_back(*it);
    for(; it->isLetter() && it != str.cend(); it++)
        elem.push_back(*it);
    for(; it != str.cend(); it++)
        index.push_back(*it);

    real_nucl = nucl.toInt();
    real_elem = elem;
    real_index = index.toDouble();

    if(index.isEmpty())
        real_index = 1.0;

    Element e = dt_sld.get_element(real_elem, real_nucl);

    if(e.is_empty())
        return false;

    ChemicalFormulaElement save_element(e, real_index);
    current->add_elem(save_element);
    return true;
}

bool Formula::close_bracket(QString line)
{
    line.remove(0, 1);
    current->set_index(line.toDouble());
    if(line.isEmpty())
        current->set_index(1.0);

    return move_to_parent();
}

bool Formula::open_bracket(QString)
{
    return add_child();
}

bool Formula::square_brackets(QString line)
{
    bool correct;
    line.remove('[');
    line.remove(']');
    double val = line.toDouble(&correct);

    if(!correct)
        return false;

    if(val == 0.0)
        return false;

    squarebrackets_index.push_back(val);
    subformulas.push_back(root);
    current = root = new SubFormula();

    return true;
}


bool Formula::is_correct(QString str)
{
    if(str.isEmpty())
        return false;
    clear();
    auto size = str.size();
    while(!str.isEmpty())
    {
        auto c = str.at(0);

        if(c == '(')
        {
            QString line = remove_open_bracket(str);
            if(line.isEmpty())
                return false;
            open_bracket(line);
        }
        if(c.isUpper() || c == '^')
        {
            QString line = remove_element(str);
            if(line.isEmpty())
                return false;
            if(!add_element(line))
                return false;
        }
        if(c == ')')
        {
            QString line = remove_close_bracket_index(str);
            if(line.isEmpty())
                return false;
            if(!close_bracket(line))
                return false;
        }
        if(c == '[')
        {
            QString line = remove_square_brackets(str);
            if(current != root)
                return false;
            if(line.isEmpty())
                return false;
            square_brackets(line);
        }

        if(size == str.size())
            return false;
        size = str.size();
    }


    if(!subformulas.empty() && !root->empty())
        return false;



    return str.isEmpty();
}

std::vector<ChemicalFormulaElement> Formula::get_elements(QString str)
{
    if(!is_correct(str))
        return std::vector<ChemicalFormulaElement>();
    if(subformulas.size() != squarebrackets_index.size())
        return std::vector<ChemicalFormulaElement>();
    if(subformulas.empty())
        return root->get_elements();

    std::vector<ChemicalFormulaElement> result;

    for(std::size_t i = 0; i < subformulas.size(); i++)
    {
        auto mass = subformulas[i]->summ_mass();
        auto temp = subformulas[i]->get_elements();
        auto index = squarebrackets_index[i];

        for(auto p : temp)
            p.mult(index/mass);
        result.insert(result.cend(), temp.cbegin(), temp.cend());
    }

    return result;
}


bool Formula::move_to_parent()
{
    if(is_root())
        return false;

    current = current->back();
    return true;
}

bool Formula::add_child()
{
    current = current->add_subformula();
    return true;
}

QString Formula::remove_int_value(QString &str)
{
    QString value;
    auto it = str.cbegin();

    while((*it).isDigit())
    {
        value.push_back(*it);
        it++;
        if(it == str.cend())
            break;
    }
    str.erase(str.cbegin(), it);

    return value;
}

QString Formula::remove_element_name(QString &str)
{
    QString element_name;
    if(str.isEmpty())
        return QString();

    if(str.at(0).isUpper())
    {
        element_name.push_back(str.at(0));
        str.remove(0, 1);
    }

    auto it = str.cbegin();
    while(it->isLower())
    {
        element_name.push_back(*it);
        it++;
        if(it == str.cend())
            break;
    }
    str.erase(str.cbegin(), it);

    return element_name;
}

QString Formula::remove_double_index(QString &str)
{
    if(str.isEmpty())
        return QString();

    QString::ConstIterator c_it = str.cbegin();
    QString index;

    while((*c_it).isDigit() || (*c_it) == '.')
    {
        index.push_back(*c_it);
        c_it++;
        if(c_it == str.cend())
            break;
    }
    str.erase(str.cbegin(), c_it);

    bool correct;
    index.toDouble(&correct);
    if(!correct)
        return QString();

    return index;
}

QString Formula::remove_element(QString &str)
{
    QString elem;
    QString name;
    QString index;
    if(str.isEmpty())
        return QString();

    if(str.at(0) == '^')
    {
        elem.push_back(str.at(0));
        str.remove(0, 1);
        elem += remove_int_value(str);
    }
    if(str.isEmpty())
        return QString();

    name    += remove_element_name(str);
    if(name.isEmpty())
        return QString();

    index   += remove_double_index(str);

    return elem + name + index;
}

QString Formula::remove_open_bracket(QString &str)
{
    QString result;
    if(str.isEmpty())
        return QString();

    if(str.at(0) == '(')
    {
        result = str.at(0);
        str.remove(0, 1);
    }
    return result;
}

QString Formula::remove_close_bracket_index(QString &str)
{
    QString result;
    if(str.isEmpty())
        return QString();

    if(str.at(0) == ')')
    {
        result.push_back(str.at(0));
        str.remove(0, 1);
        return result + remove_double_index(str);
    }
    return QString();
}

QString Formula::remove_square_brackets(QString &str)
{
    if(str.isEmpty())
        return QString();

    if(str.at(0) != '[')
        return QString();

    str.remove(0, 1);
    QString value = remove_double_index(str);

    if(str.at(0) != ']')
        return QString();
    if(value.isEmpty())
        return QString();

    str.remove(0, 1);

    return '[' + value + ']';
}


void Formula::clear()
{
    root->clear();
    current = root;
    for(auto p : subformulas)
        delete p;
    subformulas.clear();
    squarebrackets_index.clear();
}
