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

public:
    explicit ResultLine(QWidget *parent = nullptr);
    void setText(QString label, QString combobox);
    void setResult(QString text);
    void setResult(double value, double error);
    void setResult(double value);
    QHBoxLayout* getLayout() { return layout; };
    // void setResult(double res, double err);

signals:
};

#endif // RESULTLINE_H
