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

    QString mantissa_string(QString);

    QString set_result(double, double);

public:
    explicit ResultLine(QWidget *parent = nullptr);
    void setText(QString label, QString combobox);

    void setResult(QString text);
    void setResult(double value, double error);
    void setResult(double value);

    void setTip(QString line)   { label->setToolTip(line); }
    QHBoxLayout* getLayout()    { return layout; };
    // void setResult(double res, double err);

signals:
};

#endif // RESULTLINE_H
