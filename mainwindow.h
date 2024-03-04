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
#include "coresld.h"

class MainWindow : public QMainWindow
{
    CoreSLD *core = nullptr;

    QValidator *valid_double = nullptr; //new QDoubleValidator()

    QWidget *centralWidget = nullptr;
    ChemicalTextEdit *formula_TextEdit = nullptr;
    ChemicalLabel *formula_Label = nullptr;
    QLineEdit *density_LineEdit = nullptr;
    QLineEdit *result_LineEdit = nullptr;
    QPushButton *calculate_PushButton = nullptr;
    QVBoxLayout *chemicalLayout = nullptr;
    QHBoxLayout *chemical_sublayout = nullptr;

    QGroupBox *inputdata_group_box = nullptr;

    QMenuBar *main_menubar = nullptr;
    QStatusBar *main_statusbar = nullptr;

    void createmenubar();
    void createstatusbar();

    void error_message();


    Q_OBJECT


    QWidget* setChemicalLine();
    void setLayouts();
    void setSignals();

// private slots:
    void initialize();
    void calculate();
private slots:
    void pressCalculateButton();

public:

    MainWindow(QWidget *parent = nullptr);
    // void show();
    ~MainWindow();
};
#endif // MAINWINDOW_H
