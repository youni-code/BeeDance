#include "resultline.h"

QString ResultLine::mantissa_string(QString value)
{
    if(value[0] == '-')
        value.insert(2, ".");
    else
        value.insert(1, ".");
    return value;
}

QString ResultLine::add_point(double val, double err)
{
    QString s_value = QString::number(val);
    QString s_error = QString::number(err);

    if(s_value.at(0) == '-')
        s_value.insert(2, '.');
    else
        s_value.insert(1, '.');

    return s_value + "(" + s_error + ")";
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
    if(value == 0.0 || error == 0.0) return textedit->setText("---");
    if(error == 0.0) return textedit->setText(QString::number(value));

    double exp_value = exp(value);
    double exp_error = exp(error);
    double min_exp = std::min(exp_value, exp_error);
    double max_exp = std::max(exp_value, exp_error);

    double mantissa_value = mantissa(value, min_exp); // мантисса без дробной части
    double mantissa_error = mantissa(error, min_exp); // мантисса без дробной части

    QString result = mantissa_string(QString::number(mantissa_value));

    result = add_point(mantissa_value, mantissa_error) + "E" + QString::number(max_exp);
    return textedit->setText(result);
}

void ResultLine::setResult(double value)
{
    textedit->setText(QString::number(value));
}

void ResultLine::setTip(QString line)
{
    label->setToolTip(line);
}
