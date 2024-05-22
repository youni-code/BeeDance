#include "resultline.h"
#include <QDebug>

QString ResultLine::input_result(double v, double e)
{
    if(e > v) return input_error_more_value(v, e);

    if(v == 0.0 || e == 0.0)
        return "---";
    if(e == 0.0)
        return QString::number(v);

    // log10 of value and error
    double exp_v = std::floor(std::log10(std::abs(v)));
    double exp_e = std::floor(std::log10(std::abs(e)));
    double min_exp = std::min(exp_v, exp_e);
    double max_exp = std::max(exp_v, exp_e);

    // Integer part has as many digits as need to have 2 digits to show error
    double val_v = v * std::pow(10, -min_exp + 1);
    double val_e = e * std::pow(10, -min_exp + 1);

    double end_v = std::round(val_v);
    double end_e = std::round(val_e);

    // convert all digits in string
    QString full_v = QString::number(std::floor(end_v), 'g', std::floor(std::log10(end_v)) + 1);;
    QString full_e = QString::number(std::floor(end_e), 'g', std::floor(std::log10(end_e)) + 1);;

    QString result = full_v + "(" + full_e + ")e" + QString::number(max_exp);

    if (result.at(0) == '-')
        result.insert(2, '.');
    else
        result.insert(1, '.');

    return result;
}

QString ResultLine::input_error_more_value(double v, double e)
{
    qDebug() << "value: " << v << " " << e;

    if(v == 0.0 || e == 0.0)
        return "---";
    if(e == 0.0)
        return QString::number(v);

    // log10 of value and error
    double exp_v = std::floor(std::log10(std::abs(v)));
    double exp_e = std::floor(std::log10(std::abs(e)));
    double min_exp = std::min(exp_v, exp_e);
    double max_exp = std::max(exp_v, exp_e);

    // Integer part has as many digits as need to have 2 digits to show error
    // double val_v = v * std::pow(10, -min_exp + 1);
    // double val_e = e * std::pow(10, -min_exp + 1);
    double val_v = v * std::pow(10, -max_exp + 1);
    double val_e = e * std::pow(10, -max_exp + 1);

    double end_v = std::round(val_v);
    double end_e = std::round(val_e);
    // qDebug() << end_v << " " << end_e;

    // convert all digits in string
    QString full_v = QString::number(std::floor(end_v), 'g', std::floor(std::log10(end_v)) + 1);;
    QString full_e = QString::number(std::floor(end_e), 'g', std::floor(std::log10(end_e)) + 1);;


    if(full_v.at(0) == '-')
    {
        if(full_v.size() == 3)
            full_v.insert(2, '.');
        else
            full_v.insert(0, "0.");
    }
    else
    {
        if(full_v.size() == 2)
            full_v.insert(1, '.');
        else
            full_v.insert(0, "0.");
    }


    QString result = full_v + "(" + full_e + ")e" + QString::number(min_exp);

    return result;
}


ResultLine::ResultLine(QWidget *parent)
    : QWidget{parent}
{
    QFont font;
    font.setPointSize(12);

    layout = new QHBoxLayout;

    label = new QLabel;
    textedit = new QLineEdit;
    combobox = new QComboBox;

    this->setLayout(layout);

    layout->addWidget(label);
    layout->addWidget(textedit);
    layout->addWidget(combobox);

    textedit->setReadOnly(true);

    label->setFixedWidth(70);
    label->setFont(font);

    combobox->setFixedWidth(80);
}

void ResultLine::set_text(QString slabel, QString scombobox)
{
    label->setText(slabel);
    combobox->addItem(scombobox);
}








