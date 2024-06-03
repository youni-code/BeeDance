#include <QApplication>
// #include <QFileDialog>
#include <QDesktopServices>
#include "mainwindow.h"

void MainWindow::set_menubar()
{
    QMenu *menu_file = new QMenu("File", menubar);
    menu_file->addAction(open_action);
    menu_file->addSeparator();
    menu_file->addAction(saveas_action);
    menu_file->addSeparator();
    menu_file->addAction(exit_action);

    QMenu *menu_help = new QMenu("Help", menubar);
    menu_help->addAction(help_action);

    menubar->addMenu(menu_file);
    menubar->addSeparator();
    menubar->addMenu(menu_help);

    this->setMenuBar(menubar);
    this->setStatusBar(statusbar);
}
void MainWindow::set_widgets()
{
    v_layout->addWidget(iw);
    v_layout->addStretch(10);
    v_layout->addWidget(rw);
}


void MainWindow::set_signals()
{
    connect(iw,             SIGNAL(push_button()), this,    SLOT(pressed_calc_button()));
    connect(exit_action,    SIGNAL(triggered()),   qApp,    SLOT(exit()));
    connect(open_action,    SIGNAL(triggered()),   this,    SLOT(open_file_submenu()));
    connect(saveas_action,  SIGNAL(triggered()),   this,    SLOT(saveas_file_submenu()));
    connect(help_action,    SIGNAL(triggered()),   this,    SLOT(help_submenu()));
}

void MainWindow::set_data()
{
    core->set_formula(iw->formula());
    core->set_density(iw->density());
    core->set_wavelength(iw->lambda());
}

void MainWindow::pressed_calc_button()
{
    statusbar->showMessage("Calculating...");
    rw->clear();

    auto errors = errors_list();
    if(!errors.isEmpty())
        return statusbar->showMessage("There are some mistakes: " + errors, 7000);

    set_data();
    calculation();
    statusbar->showMessage("Completed. ", 7000);
}

void MainWindow::calculation()
{
    if(core->valid_sld())
        rw->set_re_sld(core->get_sld(), core->get_sld_err());
    if(core->valid_sld_im())
        rw->set_im_sld(core->get_sld_im(), core->get_sld_im_err());

    if(core->valid_potv())
        rw->set_re_v(core->get_potv(), core->get_potv_err());
    if(core->valid_potv_im())
        rw->set_im_v(core->get_potv_im(),                core->get_potv_im_err());

    if(core->valid_charact_wavelenght())
        rw->set_lambda_c(core->get_charact_wavelength(),     core->get_charact_wavelength_error());
    if(core->valid_critical_angle())
        rw->set_tetta_c(core->get_critical_angle(),         core->get_critical_angle_error());

    if(core->valid_critical_momenutm())
        rw->set_q_c(core->get_critical_momentum(),      core->get_critical_momentum_error());
    if(core->valid_mu())
        rw->set_mu(core->get_mu(), core->get_mu_error());

    if(core->valid_true_absorbtion())
        rw->set_mu_a(core->get_true_absorbtion(),        core->get_true_absorbtion_error());
    if(core->valid_incoherrent_scattering())
        rw->set_mu_inc(core->get_incoherrent_scattering(), core->get_incoherrent_scattering_error());
}

QString MainWindow::errors_list()
{
    QString error_line;
    core->set_formula(iw->formula());

    if(!core->is_line_correct())
        error_line += "Line incorrect;\t";
    if(iw->density() <= 0.0)
        error_line += "Density incorrect;\t";
    if(iw->lambda() <= 0.0)
        error_line += "Lambda incorrect;\t";

    return error_line;
}

void MainWindow::initialize()
{
    core = new CoreSLD();

    central_widget = new QWidget(this);

    v_layout = new QVBoxLayout(central_widget);
    rw = new ResultsWidget(central_widget);
    iw = new InputWidget(central_widget);

    menubar =  new QMenuBar(central_widget);
    exit_action =   new QAction("Exit", menubar);
    open_action =   new QAction("Open...", menubar);
    saveas_action = new QAction("Save as...", menubar);
    help_action =   new QAction("Help...", menubar);

    statusbar = new QStatusBar(central_widget);
}


void MainWindow::open_file_submenu()
{
    // QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "", "text format(*.txt)");
}

void MainWindow::saveas_file_submenu()
{
    // QString filters("Music files (*.mp3);;Text files (*.txt);;All files (*.*)");
    // QString defaultFilter("Text files (*.txt)");

    // QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(), filters, &defaultFilter);
}

void MainWindow::help_submenu()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile("data/help.pdf"));
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initialize();
    set_menubar();
    set_widgets();

    this->setWindowTitle("BeeDance");
    this->setCentralWidget(central_widget);

    set_signals();
}

MainWindow::~MainWindow()
{
    delete core;
}
