#include "formula.h"

bool Formula::add_element(QString str)
{
    QString nucl;
    QString elem;
    QString index;

    int     real_nucl;
    QString real_elem;
    double  real_index;


    QString::ConstIterator it = str.cbegin();

    if((*it) == '^') str.remove(0, 1); // if the first element is ^ - remove it.

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

    Element e = dt_sld.getElement(real_elem, real_nucl);
    if(e.is_empty()) return false;


    ChemicalFormulaElement *save_element = new ChemicalFormulaElement(e, real_index);
    current->add_element(save_element);
    return true;
}

void Formula::close_bracket(QString line)
{
    line.remove(0, 1);
    current->set_index(line.toDouble());
    if(line.isEmpty()) current->set_index(1.0);
    move_to_parent();
}

void Formula::open_bracket(QString)
{
    add_child();
}

void Formula::square_brackets(QString line)
{
    line.remove('[');
    line.remove(']');
    squarebrackets_index.push_back(line.toDouble());
}


bool Formula::add_line(QString str)
{
    auto size = str.size();
    while(!str.isEmpty())
    {
        QString r_open_bracket = remove_open_bracket(str);
        if(!r_open_bracket.isEmpty())
        {
            open_bracket(r_open_bracket);
            continue;
        }
        QString r_element = remove_element(str);
        if(!r_element.isEmpty())
        {
            add_element(r_element);
            continue;
        }
        QString r_close_bracket = remove_close_bracket_index(str);
        if(!r_close_bracket.isEmpty())
        {
            close_bracket(r_close_bracket);
            continue;
        }
        QString r_square_brackets = remove_square_brackets(str);
        if(!r_square_brackets.isEmpty())
        {
            square_brackets(r_square_brackets);
            continue;
        }
        if(size == str.size()) break;
        size = str.size();
    }

    return str.isEmpty();
}


void Formula::move_to_parent()
{
    current = current->back();
}

void Formula::add_child()
{
    current = current->add_subformula();
}

QString Formula::remove_int_value(QString &str)
{
    QString value;
    auto it = str.cbegin();

    while((*it).isDigit())
    {
        value.push_back(*it);
        it++;
        if(it == str.cend()) break;
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
        if(it == str.cend()) break;
    }
    str.erase(str.cbegin(), it);

    return element_name;
}

QString Formula::remove_double_index(QString &str)
{
    if(str.isEmpty()) return QString();

    QString::ConstIterator c_it = str.cbegin();
    QString index;

    while((*c_it).isDigit() || (*c_it) == '.')
    {
        index.push_back(*c_it);
        c_it++;
        if(c_it == str.cend()) break;
    }
    str.erase(str.cbegin(), c_it);

    bool correct;
    index.toDouble(&correct);
    if(!correct) return QString();


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
    if(str.isEmpty()) return QString();

    name    += remove_element_name(str);
    if(name.isEmpty()) return QString();

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

    if(str.at(0) != ']') return QString();
    if(value.isEmpty()) return QString();

    str.remove(0, 1);

    return '[' + value + ']';
}


Formula::Formula()
{
    root = new SubFormula(nullptr);
    current = root;
}

std::vector<ChemicalFormulaElement *> Formula::get_elements()
{
    return root->get_elements();
}



// bool Formula::add_line(QString str)
// {
//     // QString temp;
//     while(!str.isEmpty())
//     {
//         QChar a = str.at(0);


//         if(a == '(')
//         {
//             add_child();
//             str.remove(0, 1);
//             continue;
//         }
//         if(a == ')')
//         {
//             if(is_root()) return false;
//             back();
//             str.remove(0, 1);
//             continue;

//         }

//         if(a == '[')
//         {
//             if(is_back())
//                 return false; // must be on the root
//             str.remove(0, 1);

//             QString num;

//             for(auto n : str)
//             {
//                 if(n == ']')
//                     break;
//                 num += n;
//             }
//             str.remove(0, num.size());
//             if(str.isEmpty()) // There is no closing square bracket
//                 return false;
//             str.remove(0, 1); // remove closing square bracket
//             bool right;
//             double sq_index = num.toDouble(&right);
//             if(!right)
//                 return false; // if something wrong with convertion return false
//             squarebrackets_index.push_back(sq_index);
//         }
//         if(a == '^')
//         {
//             QString elem;
//             elem.push_back(a);
//             str.remove(0, 1);

//         }
//         if(a.isUpper())
//         {

//         }


//     }



//     // add_element(str);
//     // QString temp;








//     return false;
// }
