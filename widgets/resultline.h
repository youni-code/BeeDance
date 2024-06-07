#ifndef RESULTLINE_H
#define RESULTLINE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>

class ResultLine : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *layout;
    QLabel      *label;
    QLineEdit   *textedit;
    QComboBox   *combobox;

    QString input_result(double, double);
    QString input_error_more_value(double, double);

public:
    explicit ResultLine(QWidget *parent = nullptr);
    void set_text(QString label, QString combobox);

    void set_result(QString text)               { textedit->setText(text); }
    void set_result(double value, double error) { textedit->setText(input_result(value, error)); }
    void set_result(double value)               { textedit->setText(QString::number(value)); }

    void set_tip(QString line)                  { label->setToolTip(line); }

signals:
};

#endif // RESULTLINE_H
