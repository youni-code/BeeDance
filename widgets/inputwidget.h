#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "chemicaltextedit.h"
#include "chemicallabel.h"

class InputWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout      *chemical_layout   = nullptr;
    ChemicalTextEdit *formula_TextEdit  = nullptr;
    ChemicalLabel    *formula_Label     = nullptr;

    QHBoxLayout *density_sublayout      = nullptr;
    QLabel      *density_label          = nullptr;
    QLineEdit   *density_LineEdit       = nullptr;
    QComboBox   *density_ComboBox       = nullptr;

    QHBoxLayout *lambda_sublayout       = nullptr;
    QLabel 		*lambda_label           = nullptr;
    QLineEdit 	*lambda_LineEdit        = nullptr;
    QComboBox 	*lambda_ComboBox        = nullptr;

    QVBoxLayout *lamb_dens_sublayout    = nullptr;
    QHBoxLayout *pushbutton_sublayout   = nullptr;
    QPushButton *calculate_PushButton   = nullptr;

    QHBoxLayout *button_sublayout       = nullptr;
    QVBoxLayout *main_sublayout         = nullptr;

    void initialize();
    void set_formulaline();
    void set_densityline();
    void set_density_lambda_layout();
    void set_formula_layout();

    void set_signals();

public:
    explicit InputWidget(QWidget *parent = nullptr);

    QString formula() const { return formula_TextEdit->toPlainText(); }
    double  density() const { return density_LineEdit->text().toDouble(); }
    double  lambda()  const { return lambda_LineEdit->text().toDouble(); }

signals:
    void push_button();
};

#endif // INPUTWIDGET_H
