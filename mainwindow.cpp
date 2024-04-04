#include <QApplication>
#include "mainwindow.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QString>
#include <QRegularExpression>

void MainWindow::set_menubar()
{
    QMenu *menu_file = new QMenu("File", main_menubar);
    menu_file->addAction("Open...");
    menu_file->addSeparator();
    menu_file->addAction("Save");
    menu_file->addAction("Save as...");
    menu_file->addSeparator();
    menu_file->addAction("Exit");

    QMenu *menu_help = new QMenu("Help", main_menubar);
    menu_help->addAction("Help...");

    QMenu *menu_view = new QMenu("View");
    menu_view->addAction("Style...");

    main_menubar->addMenu(menu_file);
    main_menubar->addMenu(menu_view);
    main_menubar->addSeparator();
    main_menubar->addMenu(menu_help);
}
void MainWindow::show_sld_error_message()
{
    rl_sld->setResult("Error!");
    if(!core->is_line_correct())
        return main_statusbar->showMessage("Error! Something wrong with the input line", 5000);
    if(!core->is_density_correct())
        return main_statusbar->showMessage("Error! Density is wrong ", 5000);
    if(!core->is_all_data_exist())
        return main_statusbar->showMessage("Error! There aren't some elements", 5000);

    return;
}
void MainWindow::set_widgets()
{
    set_chemicalline();
    set_densityline();
    set_results();

    this->setMenuBar(main_menubar);
    this->setStatusBar(main_statusbar);
}

void MainWindow::set_chemicalline()
{
    auto f = formula_TextEdit->font();
    f.setPointSize(16);

    formula_Label->setFont(f);

    formula_TextEdit->setAcceptRichText(false);
    formula_TextEdit->setText("H2ONeCaMgFeCo");
    formula_TextEdit->setMaximumHeight(1.2 * density_LineEdit->height());
    formula_TextEdit->setFont(f);
}

void MainWindow::set_densityline()
{
    density_LineEdit->setValidator(new QDoubleValidator());
    density_LineEdit->setText("1.0");

    density_ComboBox->addItem("g/cm³");

    calculate_PushButton->setText("Run");
}

void MainWindow::set_results()
{
    rl_sld->setText("SLD", "1/Å²");
    rl_pot_v->setText("Π<sub>V</sub>", "neV");
    rl_ch_wl->setText("λ<sub>c</sub>", "---");
    rl_cr_ang->setText("θ<sub>c</sub>", "---");

    rl_cr_mom->setText("q<sub>c</sub>", "1/cm");
    rl_atl_c->setText("μ", "1/cm");
    rl_absorb->setText("μ<sub>α</sub>", "1/cm");
    rl_scatt->setText("μ<sub>inc</sub>", "1/cm");
}

void MainWindow::set_sldresult()
{
}

void MainWindow::set_layouts()
{
    central_widget->setLayout(chemical_layout);

    chemical_layout->addWidget(formula_TextEdit);
    chemical_layout->addWidget(formula_Label);
    chemical_layout->setAlignment(Qt::AlignTop);


    chemical_layout->addLayout(density_sublayout);
    density_sublayout->addWidget(new QLabel("Density:"));
    density_sublayout->addWidget(density_LineEdit);
    density_sublayout->addWidget(density_ComboBox);
    density_sublayout->addWidget(calculate_PushButton);

    chemical_layout->addStretch(10);


    chemical_layout->addWidget(rl_sld);
    chemical_layout->addWidget(rl_pot_v);
    chemical_layout->addWidget(rl_ch_wl);
    chemical_layout->addWidget(rl_cr_ang);

    chemical_layout->addWidget(rl_cr_mom);
    chemical_layout->addWidget(rl_atl_c);
    chemical_layout->addWidget(rl_absorb);
    chemical_layout->addWidget(rl_scatt);


}

void MainWindow::set_signals()
{
    connect(formula_TextEdit, SIGNAL(changeFormula(QString)), formula_Label, SLOT(setFormula(QString)));
    connect(calculate_PushButton, SIGNAL(pressed()), this, SLOT(press_calculate_button()));

    emit formula_TextEdit->changeFormula(formula_TextEdit->toPlainText());
}

void MainWindow::initialize()
{
    core = new CoreSLD();

    central_widget = new QWidget(this);

    main_menubar = new QMenuBar(central_widget);
    main_statusbar = new QStatusBar(central_widget);


    chemical_layout =        new QVBoxLayout(central_widget);
    formula_TextEdit = new ChemicalTextEdit();
    formula_Label = new ChemicalLabel();


    density_sublayout =    new QHBoxLayout();
    density_LineEdit = new QLineEdit(central_widget);
    density_ComboBox = new QComboBox();
    calculate_PushButton = new QPushButton(central_widget);


    rl_sld = new ResultLine();
    rl_pot_v = new ResultLine();
    rl_ch_wl = new ResultLine();
    rl_cr_ang = new ResultLine();
    rl_cr_mom = new ResultLine();
    rl_atl_c = new ResultLine();
    rl_absorb = new ResultLine();
    rl_scatt = new ResultLine();
}

QString MainWindow::result_string(double value, double error)
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

    return result;
}

QString MainWindow::mantissa_string(QString value)
{
    if(value[0] == '-')
        value.insert(2, ".");
    else
        value.insert(1, ".");
    return value;
}

void MainWindow::press_calculate_button()
{
    main_statusbar->showMessage("Calculating...");

    core->setFormula(formula_TextEdit->toPlainText());
    core->setDensity(density_LineEdit->text().toDouble());

    if(!core->is_correct()) return show_sld_error_message();

    double result_sld = core->get_sld();
    double error_sld = core->get_sld_err();

    double result_pot_v = core->get_potv();

    rl_sld->setResult(result_sld, error_sld);
    rl_pot_v->setResult(result_pot_v, result_pot_v/100);

    main_statusbar->showMessage("Completed", 5000);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initialize();
    set_menubar();
    set_widgets();
    set_layouts();
    this->setWindowTitle("BeeDance");
    this->setCentralWidget(central_widget);

    set_signals();
}

MainWindow::~MainWindow()
{
}
