#include "resultline.h"

QString ResultLine::mantissa_string(QString value)
{
    if(value[0] == '-')
        value.insert(2, ".");
    else
        value.insert(1, ".");
    return value;
}

ResultLine::ResultLine(QWidget *parent)
    : QWidget{parent}
{
    layout = new QHBoxLayout;

    label = new QLabel;
    textedit = new QLineEdit;
    combobox = new QComboBox;

    this->setLayout(layout);

    layout->addWidget(label);
    layout->addWidget(textedit);
    layout->addWidget(combobox);

    textedit->setReadOnly(true);

    label->setToolTip("help");
    label->setFixedWidth(30);

    combobox->setFixedWidth(80);
    // this->setToolTip("hhhhh");
}

void ResultLine::setText(QString slabel, QString scombobox)
{
    label->setText(slabel);
    combobox->addItem(scombobox);
}

void ResultLine::setResult(QString text)
{
    textedit->setText(text);
}

void ResultLine::setResult(double value, double error)
{
    double exp_value = std::floor(std::log10(std::abs(value)));
    double exp_error = std::floor(std::log10(std::abs(error)));

    double min_exp = std::min(exp_value, exp_error);

    double mantissa_value = std::round(value / std::pow(10, min_exp - 1)); // мантисса без дробной части
    double mantissa_error = std::round(error / std::pow(10, min_exp - 1)); // мантисса без дробной части


    QString result = mantissa_string(QString::number(std::round(value / std::pow(10, min_exp - 1))));
    QString value_str = QString::number(std::copysign(mantissa_value, value) * std::pow(10, min_exp - 1));
    qDebug() << value_str << "count of digits: "<< value_str.count("[0-9]");
    qDebug() << "value_str" << value_str;

    if(value_str.split('e').size() == 2)
        result += "(" + QString::number(mantissa_error) + ")E" + value_str.split('e').last();
    else
        result += "(" + QString::number(mantissa_error) + ")";

    textedit->setText(result);


    // return result;

}
