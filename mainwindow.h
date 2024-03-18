#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chemicaltextedit.h"
#include "chemicallabel.h"

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include "coresld.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CoreSLD *core = nullptr;
    QWidget *central_widget = nullptr;

    QMenuBar *main_menubar = nullptr;
    QStatusBar *main_statusbar = nullptr;

    QVBoxLayout *chemical_layout = nullptr;
    ChemicalTextEdit *formula_TextEdit = nullptr;
    ChemicalLabel *formula_Label = nullptr;

    QHBoxLayout *density_sublayout = nullptr;
    QLineEdit *density_LineEdit = nullptr;
    QComboBox *density_ComboBox = nullptr;
    QPushButton *calculate_PushButton = nullptr;

    QHBoxLayout *sldresult_sublayout = nullptr;
    QLabel      *sldresult_Label = nullptr;
    QLineEdit   *sldresult_LineEdit = nullptr;
    QComboBox   *sldresult_combobox = nullptr;

    QHBoxLayout *r2_layout = nullptr;
    QLabel      *r2_label = nullptr;
    QLineEdit   *r2_lineedit = nullptr;
    QComboBox   *r2_combobox = nullptr;

    void initialize();

    void set_menubar();
    void set_statusbar();

    void set_widgets();
    void set_chemicalline();
    void set_densityline();
    void set_results();
    void set_sldresult();

    void set_layouts();
    void set_signals();

    void show_sld_error_message();

    QString result_string(double value, double error);
    QString mantissa_string(QString value);
private slots:
    void press_calculate_button();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
