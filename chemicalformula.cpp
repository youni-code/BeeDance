#include "chemicalformula.h"
#include <QRegularExpression>
#include <deque>


ChemicalFormula::ChemicalFormula(QString line)
{
    formula = line;
}
QString::ConstIterator ChemicalFormula::it_on_SecondElement(const QString &line)
{
    auto it = line.cbegin();
    if(line.cbegin() == line.cend()) return it;
    for(; it != line.cend(); it++) // находим заглавный символ первого элемента
        if((*it).isUpper()) break;
    it++;
    for(; it != line.cend(); it++)
        if((*it).isUpper() || (*it) == '^') break;

    return it;
}
SimpleFormulaElement ChemicalFormula::readIsotope(QString line)
{
    if(line.isEmpty()) return SimpleFormulaElement("", 0, 0.0);

    if(line[0] == '^') line.remove(0, 1); // удаляем знак ^ если есть.

    QString nucl;
    auto it(line.cbegin());
    for(; it->isDigit(); it++) nucl.push_back(*it);
    long nucleons = nucl.toLong();

    QString element;
    for(; it->isLetter(); it++) element.push_back(*it);

    QString id(getLine(it, line.cend()));
    double index = id.toDouble();
    if(id.isEmpty()) index = 1.0;

    SimpleFormulaElement el(element, nucleons);
    el.setindex(index);
    return el;

}
bool ChemicalFormula::hasBrackets(QString line)
{
    static QRegularExpression open_brackets("[(]");
    static QRegularExpression close_brackets("[)]");

    for(auto it(line.cbegin()); it != line.cend(); it++)
    {
        if(QString(*it).contains(open_brackets)) return true;
        if(QString(*it).contains(close_brackets)) return true;
    }
    return false;
}
QString ChemicalFormula::getLine(QString::ConstIterator cbegin, QString::ConstIterator cend)
{
    QString result;

    if(cbegin == nullptr || cend == nullptr) return result;

    for(auto it(cbegin); it != cend; it++) result.push_back(*it);
    return result;
}
QString ChemicalFormula::getLine(std::pair<QString::ConstIterator, QString::ConstIterator> p)
{
    return getLine(p.first, p.second);
}
std::vector<SimpleFormulaElement> ChemicalFormula::getElements(QString subformula)
{
    std::vector<SimpleFormulaElement> result;
    QString temp_formula = subformula;

    while(hasBrackets(temp_formula))
    {
        auto iters_brackets_with_index = (brackets_index_inside(temp_formula)); // получаем выражение со скобками и индексом
        QString brackets_with_index = getLine(iters_brackets_with_index); // получаем полное выражение
        temp_formula.erase(iters_brackets_with_index.first, iters_brackets_with_index.second); // удаляем из исходной строки
        QString inner_brackets = getLine(brackets_inside(brackets_with_index)); // получаем внутреннее выражение
        double brackets_index = get_index(brackets_with_index); // получаем индекс
        std::vector<SimpleFormulaElement> temp_res = getElements(inner_brackets);
        multiple_on_index(temp_res, brackets_index);
        result.insert(result.end(), temp_res.begin(), temp_res.end());
    }

    while(!temp_formula.isEmpty())
    {
        result.push_back(get_firstElement(temp_formula));
        temp_formula = del_firstElement(temp_formula);
    }

    return result;
}
std::pair<QString::ConstIterator, QString::ConstIterator> ChemicalFormula::brackets_index_inside(QString const &line)
{
    std::pair<QString::ConstIterator, QString::ConstIterator> result(nullptr, nullptr);
    static QRegularExpression open_brackets("[(]");
    static QRegularExpression close_brackets("[)]");

    std::deque<QChar> deq_brackets;

    QString::ConstIterator it;
    for(it = line.begin(); it != line.end(); it++)
    {
        if (QString(*it).contains(open_brackets))
        {
            if(deq_brackets.empty())
            {
                result.first = it;
                result.second = it;
            }
            deq_brackets.push_back(*it);
            deq_brackets.push_back(')');
        }
        if (QString(*it).contains(close_brackets))
        {
            deq_brackets.pop_back();
            deq_brackets.pop_back();

            if(deq_brackets.empty()) break;
        }
    }
    for(it++; it != line.end(); it++)
    {
        if(it->isDigit() || *it == '.') continue;
        break;
    }
    result.second = it;
    return result;
}
std::pair<QString::ConstIterator, QString::ConstIterator> ChemicalFormula::brackets_inside(const QString &line)
{
    std::pair<QString::ConstIterator, QString::ConstIterator> result(nullptr, nullptr);
    if(!hasBrackets(line)) return result; // if line doesn't have any brackets - return nullptr,nullptr

    static QRegularExpression open_brackets("[(]");
    static QRegularExpression close_brackets("[)]");

    std::deque<QChar> deq_brackets;


    QString::ConstIterator it;
    for(it = line.begin(); it != line.end(); it++)
    {
        if (QString(*it).contains(open_brackets))
        {
            if(deq_brackets.empty())
            {
                result.first = it;
                result.second = it;
            }
            deq_brackets.push_back(*it);
            deq_brackets.push_back(')');
        }
        if (QString(*it).contains(close_brackets))
        {
            deq_brackets.pop_back();
            deq_brackets.pop_back();

            if(deq_brackets.empty()) break;
        }
    }
    result.first++;
    result.second = it;
    return result;

}
double ChemicalFormula::get_index(const QString &line)
{
    if(!hasBrackets(line)) return 0.0;

    QString::ConstIterator temp_it = line.cend();
    for(auto it(line.cbegin()); it != line.cend(); it++) { if(*it == ')') temp_it = it; }

    temp_it++;

    if(temp_it == line.cend()) return 1.0;

    QString str_index = getLine(temp_it, line.cend());

    return str_index.toDouble();

}
void ChemicalFormula::multiple_on_index(std::vector<SimpleFormulaElement> &vec, double vec_index)
{
    for(auto it(vec.begin()); it != vec.end(); it++) it->mult(vec_index);
}
std::vector<SimpleFormulaElement> ChemicalFormula::getElements() // line is correct. In other way - undefined behavior
{
    return getElements(formula);
}

SimpleFormulaElement ChemicalFormula::get_firstElement(const QString line)
{
    return readIsotope(getLine(line.begin(), it_on_SecondElement(line)));
}
QString ChemicalFormula::del_firstElement(QString const line)
{
    return getLine(it_on_SecondElement(line), line.cend());
}
