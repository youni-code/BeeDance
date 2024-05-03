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
    QFont f = formula_TextEdit->font();
    f.setPointSize(18);

    formula_Label->setFont(f);
    // formula_Label.
    formula_TextEdit->setFont(f);
    formula_TextEdit->setAcceptRichText(false);
    formula_TextEdit->setMaximumHeight(1.3 * density_LineEdit->height());
    formula_TextEdit->setPlaceholderText("chemical formula e.g. H2O");
}

void MainWindow::set_densityline()
{
    QValidator *doublevalid = new QDoubleValidator();
    doublevalid->setLocale(QLocale::C);

    density_LineEdit->setValidator(doublevalid);
    density_LineEdit->setText("1.0");
    density_ComboBox->addItem("g/cm³");
    density_ComboBox->setFixedWidth(35);

    lambda_LineEdit->setValidator(doublevalid);
    lambda_LineEdit->setText("1.798");
    lambda_ComboBox->addItem("Å");

    calculate_PushButton->setText("Run");
}

void MainWindow::set_results()
{
    rl_sld->setText("Re(SLD)", "1/Å²");
    rl_sld->setTip("Real part of Scattering Length Density");

    rl_sld_im->setText("Im(SLD)", "1/Å²");
    rl_sld_im->setTip("Imaginary part of Scattering Length Density");

    rl_pot_v->setText("Re(V)", "neV");
    rl_pot_v->setTip("Real part of Potential");

    rl_pot_v_im->setText("Im(V)", "neV");
    rl_pot_v_im->setTip("Imaginary part of Potential");

    rl_ch_wl->setText("λ<sub>c</sub>", "Å");
    rl_ch_wl->setTip("Characteristic wavelength");

    rl_cr_ang->setText("θ<sub>c</sub>", "mrad/Å");
    rl_cr_ang->setTip("Critical angle");

    rl_cr_mom->setText("q<sub>c</sub>", "1/Å");
    rl_cr_mom->setTip("Critical momentum");

    rl_atl_c->setText("μ", "1/cm");
    rl_atl_c->setTip("Attenuation coefficient");

    rl_absorb->setText("μ<sub>α</sub>", "1/cm");
    rl_absorb->setTip("True absorption coefficient");

    rl_scatt->setText("μ<sub>inc</sub>", "1/cm");
    rl_scatt->setTip("Incoherent scattering attenuation");
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
    density_ComboBox->setFixedWidth(70);

    inputdata_sublayout->addLayout(lambda_sublayout);
    lambda_sublayout->addWidget(lambda_label);
    lambda_label->setFixedWidth(55);
    lambda_sublayout->addWidget(lambda_LineEdit);
    lambda_sublayout->addWidget(lambda_ComboBox);
    lambda_ComboBox->setFixedWidth(70);

    inputdata_button_sublayout->addWidget(calculate_PushButton);
    calculate_PushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void MainWindow::set_results_layout()
{
    QFont font_resultbox;
    font_resultbox.setBold(true);
    result_box->setTitle("Results");
    result_box->setFlat(false);
    result_box->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px} ");
    result_box->setAlignment(Qt::AlignCenter);
    result_box->setFont(font_resultbox);

    chemical_layout->addStretch(10);

    chemical_layout->addWidget(result_box);
    result_box->setLayout(groupbox_layout);

    groupbox_layout->addWidget(rl_sld);
    groupbox_layout->addWidget(rl_sld_im);
    groupbox_layout->addWidget(rl_pot_v);
    groupbox_layout->addWidget(rl_pot_v_im);
    groupbox_layout->addWidget(rl_ch_wl);
    groupbox_layout->addWidget(rl_cr_ang);

    groupbox_layout->addWidget(rl_cr_mom);
    groupbox_layout->addWidget(rl_atl_c);
    groupbox_layout->addWidget(rl_absorb);
    groupbox_layout->addWidget(rl_scatt);
}

void MainWindow::set_signals()
{
    connect(formula_TextEdit,       SIGNAL(changeFormula(QString)), formula_Label,  SLOT(setFormula(QString)));
    connect(calculate_PushButton,   SIGNAL(pressed()),              this,           SLOT(press_calculate_button()));

    connect(exit_action,    SIGNAL(triggered()), qApp, SLOT(exit()));
    connect(open_action,    SIGNAL(triggered()), this, SLOT(open_file_submenu()));
    connect(saveas_action,  SIGNAL(triggered()), this, SLOT(saveas_file_submenu()));
    connect(help_action,    SIGNAL(triggered()), this, SLOT(help_submenu()));

    emit formula_TextEdit->changeFormula(formula_TextEdit->toPlainText());
}

void MainWindow::calculation()
{
    core->setFormula(formula_TextEdit->toPlainText());
    core->setDensity(density_LineEdit->text().toDouble());
    core->setLambda(lambda_LineEdit->text().toDouble());


    if(core->valid_sld())
        rl_sld->setResult(      core->get_sld(),                    core->get_sld_err());
    if(core->valid_sld_im())
        rl_sld_im->setResult(   core->get_sld_im(),                 core->get_sld_im_err());

    rl_pot_v->setResult(    core->get_potv(),                   core->get_potv_err());
    rl_pot_v_im->setResult( core->get_potv_im(),                core->get_potv_im_err());

    rl_ch_wl->setResult(    core->get_charact_wavelength(),     core->get_charact_wavelength_error());
    rl_cr_ang->setResult(   core->get_critical_angle(),         core->get_critical_angle_error());

    rl_cr_mom->setResult(   core->get_critical_momentum(),      core->get_critical_momentum_error());
    rl_absorb->setResult(   core->get_true_absorbtion(),        core->get_true_absorbtion_error());

    rl_scatt->setResult(    core->get_incoherrent_scattering(), core->get_incoherrent_scattering_error());
    rl_atl_c->setResult(    core->get_mu(),                     core->get_mu_error());
}

bool MainWindow::checking()
{
    core->setFormula(formula_TextEdit->toPlainText());
    if(!core->is_line_correct()) return false;
    if(density_LineEdit->text().toDouble() <= 0.0) return false;
    if(lambda_LineEdit->text().toDouble() <= 0.0) return false;

    return true;

}

QString MainWindow::errors_list()
{
    QString error_line;
    core->setFormula(formula_TextEdit->toPlainText());

    if(!core->is_line_correct())                    error_line += "Line incorrect;\t";
    if(density_LineEdit->text().toDouble() <= 0.0)  error_line += "Density incorrect;\t";
    if(lambda_LineEdit->text().toDouble() <= 0.0)   error_line += "Lambda incorrect;\t";

    return error_line;
}

void MainWindow::non_results()
{
    rl_sld->setResult("---");
    rl_sld_im->setResult("---");

    rl_pot_v->setResult("---");
    rl_pot_v_im->setResult("---");

    rl_ch_wl->setResult("---");
    rl_cr_ang->setResult("---");

    rl_cr_mom->setResult("---");
    rl_absorb->setResult("---");

    rl_scatt->setResult("---");
    rl_atl_c->setResult("---");

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


    groupbox_layout = new QVBoxLayout();
    result_box = new QGroupBox();
    rl_sld = new ResultLine();
    rl_sld_im = new ResultLine();
    rl_pot_v = new ResultLine();
    rl_pot_v_im = new ResultLine();

    rl_ch_wl = new ResultLine();
    rl_cr_ang = new ResultLine();
    rl_cr_mom = new ResultLine();
    rl_atl_c = new ResultLine();
    rl_absorb = new ResultLine();
    rl_scatt = new ResultLine();

}

void MainWindow::press_calculate_button()
{
    main_statusbar->showMessage("Calculating...");

    if(errors_list() != "")
        return main_statusbar->showMessage("Error(s): " + errors_list(), 5000);

    non_results();
    calculation();
    main_statusbar->showMessage("Completed", 4000);
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
