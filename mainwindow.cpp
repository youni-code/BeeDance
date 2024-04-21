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
#include <QSizePolicy>

#include <QFileDialog>

void MainWindow::set_menubar()
{
    QMenu *menu_file = new QMenu("File", main_menubar);
    menu_file->addAction(open_action);
    menu_file->addSeparator();
    // menu_file->addAction("Save");
    menu_file->addAction(saveas_action);
    menu_file->addSeparator();
    menu_file->addAction(exit_action);

    QMenu *menu_help = new QMenu("Help", main_menubar);
    menu_help->addAction(help_action);

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


    formula_TextEdit->setText("H2O");
}

void MainWindow::set_densityline()
{
    density_LineEdit->setValidator(new QDoubleValidator());
    density_LineEdit->setText("1.0");
    density_ComboBox->addItem("g/cm³");
    lambda_LineEdit->setValidator(new QDoubleValidator());
    lambda_LineEdit->setText("1.798");
    lambda_ComboBox->addItem("---");


    calculate_PushButton->setText("Run");
}

void MainWindow::set_results()
{
    rl_sld->setText("SLD", "1/Å²");
    rl_sld->setTip("Scattering Length Density");

    rl_pot_v->setText("Π<sub>V</sub>", "neV");
    rl_pot_v->setTip("Potential V");

    rl_ch_wl->setText("λ<sub>c</sub>", "Å");
    rl_ch_wl->setTip("Characteristic wavelength");

    rl_cr_ang->setText("θ<sub>c</sub>", "mrad/Å");
    rl_cr_ang->setTip("Critical angle");

    rl_cr_mom->setText("q<sub>c</sub>", "1/Å");
    rl_cr_mom->setTip("Critical momentum");

    rl_atl_c->setText("μ", "1/cm");
    rl_atl_c->setTip("Attenuation coefficient");

    rl_absorb->setText("μ<sub>α</sub>", "1/cm");
    rl_absorb->setTip("Linear absorption coefficient");

    rl_scatt->setText("μ<sub>inc</sub>", "1/cm");
    rl_scatt->setTip("Incoherent scattering");
}

void MainWindow::set_sldresult()
{
}

void MainWindow::set_layouts()
{
    set_formula_layout();
    set_density_lambda_layout();
    set_results_layout();
}

void MainWindow::set_formula_layout()
{
    central_widget->setLayout(chemical_layout);

    chemical_layout->addWidget(formula_TextEdit);
    chemical_layout->addWidget(formula_Label);
    chemical_layout->setAlignment(Qt::AlignTop);

}

void MainWindow::set_density_lambda_layout()
{
    chemical_layout->addLayout(inputdata_button_sublayout);
    inputdata_button_sublayout->addLayout(inputdata_sublayout);

    inputdata_sublayout->addLayout(density_sublayout);
    density_sublayout->addWidget(density_label);
    density_label->setFixedWidth(55);
    density_sublayout->addWidget(density_LineEdit);
    density_sublayout->addWidget(density_ComboBox);
    density_ComboBox->setFixedWidth(60);

    inputdata_sublayout->addLayout(lambda_sublayout);
    lambda_sublayout->addWidget(lambda_label);
    lambda_label->setFixedWidth(55);
    lambda_sublayout->addWidget(lambda_LineEdit);
    lambda_sublayout->addWidget(lambda_ComboBox);
    lambda_ComboBox->setFixedWidth(60);

    inputdata_button_sublayout->addWidget(calculate_PushButton);
    calculate_PushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void MainWindow::set_results_layout()
{
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

    connect(exit_action, SIGNAL(triggered()), qApp, SLOT(exit()));
    connect(open_action, SIGNAL(triggered()), this, SLOT(open_file_submenu()));
    connect(saveas_action, SIGNAL(triggered()), this, SLOT(saveas_file_submenu()));
    connect(help_action, SIGNAL(triggered()), this, SLOT(help_submenu()));

    emit formula_TextEdit->changeFormula(formula_TextEdit->toPlainText());
}

void MainWindow::initialize()
{
    core = new CoreSLD();

    central_widget = new QWidget(this);

    main_menubar = new QMenuBar(central_widget);
    exit_action = new QAction("Exit");
    open_action = new QAction("Open...");
    saveas_action = new QAction("Save as...");
    help_action = new QAction("Help...");

    main_statusbar = new QStatusBar(central_widget);


    chemical_layout =        new QVBoxLayout(central_widget);
    formula_TextEdit = new ChemicalTextEdit();
    formula_Label = new ChemicalLabel();

    lamb_dens_sublayout = new QVBoxLayout();
    pushbutton_sublayout = new QHBoxLayout();

    inputdata_sublayout = new QVBoxLayout();
    inputdata_button_sublayout = new QHBoxLayout();


    density_sublayout =    new QHBoxLayout();
    density_label = new QLabel("Density:");
    density_LineEdit = new QLineEdit(central_widget);
    density_ComboBox = new QComboBox();

    lambda_sublayout = 	new QHBoxLayout();
    lambda_label = new QLabel("λ:");
    lambda_LineEdit =	new QLineEdit();
    lambda_ComboBox = 	new QComboBox();

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
    core->setLambda(lambda_LineEdit->text().toDouble());

    if(!core->is_correct()) return show_sld_error_message();

    double result_sld = core->get_sld();
    double error_sld = core->get_sld_err();

    double result_pot_v = core->get_potv();
    double result_pot_v_err = core->get_potv_err();

    double result_char_wl = core->get_charact_wavelength();
    double result_char_wle = core->get_charact_wavelength_error();

    double result_crit_angle = core->get_critical_angle();
    double result_crit_angle_err = core->get_critical_angle_error();

    double result_crit_momentum = core->get_critical_momentum();
    double result_crit_momentum_err = core->get_critical_momentum_error();

    double result_true_absorb = core->get_true_absorbtion();
    double result_true_absorb_err = core->get_true_absorbtion_error();

    double result_scatt = core->get_incoherrent_scattering();
    double result_scatt_err = core->get_incoherrent_scattering_error();

    double result_mu = core->get_mu();
    double result_mu_err = core->get_mu_error();

    rl_sld->setResult(result_sld, error_sld);
    rl_pot_v->setResult(result_pot_v, result_pot_v_err);
    rl_ch_wl->setResult(result_char_wl, result_char_wle);
    rl_cr_ang->setResult(result_crit_angle, result_crit_angle_err);
    rl_cr_mom->setResult(result_crit_momentum, result_crit_momentum_err);
    rl_absorb->setResult(result_true_absorb, result_true_absorb_err);
    rl_scatt->setResult(result_scatt, result_scatt_err);
    rl_atl_c->setResult(result_mu, result_mu_err);

    main_statusbar->showMessage("Completed", 5000);
}

void MainWindow::open_file_submenu()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "", "text format(*.txt)");
    qDebug() << filename;
}

void MainWindow::saveas_file_submenu()
{
    QString filters("Music files (*.mp3);;Text files (*.txt);;All files (*.*)");
    QString defaultFilter("Text files (*.txt)");

    /* Static method approach */
    QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(),
                                 filters, &defaultFilter);

    // QString filename = QFileDialog::getSaveFileName(this, tr("Save file as..."), QDir::currentPath(), "text format(*.txt)");
    // qDebug() << filename;

}

void MainWindow::help_submenu()
{
    QWidget *frame = new QWidget();
    frame->setGeometry(this->pos().rx(), this->pos().ry(), 800, 950);
    frame->setStyleSheet("background-image: url(data/help_screenshot.png)");
    frame->setFixedSize(frame->size());
    frame->show();
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
