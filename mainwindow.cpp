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
#include <QStyleFactory>
#include "resultswidget.h"

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

    // QMenu *menu_view = new QMenu("View");
    // light_theme = menu_view->addAction("Light style");
    // dark_theme = menu_view->addAction("Dark style");

    main_menubar->addMenu(menu_file);
    // main_menubar->addMenu(menu_view);
    main_menubar->addSeparator();
    main_menubar->addMenu(menu_help);

    this->setMenuBar(main_menubar);
    this->setStatusBar(main_statusbar);
}
void MainWindow::set_widgets()
{
    chemical_layout->addWidget(iw);
    // chemical_layout->addSpacing(10);
    chemical_layout->addStretch(10);
    chemical_layout->addWidget(rw);
}


void MainWindow::set_signals()
{
    connect(iw,   SIGNAL(push_button()),              this,           SLOT(press_calculate_button()));

    connect(exit_action,    SIGNAL(triggered()), qApp, SLOT(exit()));
    connect(open_action,    SIGNAL(triggered()), this, SLOT(open_file_submenu()));
    connect(saveas_action,  SIGNAL(triggered()), this, SLOT(saveas_file_submenu()));
    connect(help_action,    SIGNAL(triggered()), this, SLOT(help_submenu()));

    connect(light_theme, SIGNAL(triggered()), this, SLOT(set_light()));
    connect(dark_theme, SIGNAL(triggered()), this, SLOT(set_dark()));
}

void MainWindow::calculation()
{
    rw->clear();

    core->setFormula(iw->get_chemicalformula());
    core->setDensity(iw->get_density());
    core->setLambda(iw->get_lambda());


    if(core->valid_sld())       rw->set_re_sld(core->get_sld(), core->get_sld_err());
    if(core->valid_sld_im())    rw->set_im_sld(core->get_sld_im(), core->get_sld_im_err());

    if(core->valid_potv())      rw->set_re_v(core->get_potv(), core->get_potv_err());
    if(core->valid_potv_im())   rw->set_im_v( core->get_potv_im(),                core->get_potv_im_err());

    if(core->valid_charact_wavelenght()) rw->set_lambda_c(core->get_charact_wavelength(),     core->get_charact_wavelength_error());
    if(core->valid_critical_angle()) rw->set_tetta_c(core->get_critical_angle(),         core->get_critical_angle_error());

    if(core->valid_critical_momenutm()) rw->set_q_c(core->get_critical_momentum(),      core->get_critical_momentum_error());
    if(core->valid_mu()) rw->set_mu(core->get_mu(), core->get_mu_error());

    if(core->valid_true_absorbtion()) rw->set_mu_a(core->get_true_absorbtion(),        core->get_true_absorbtion_error());
    if(core->valid_incoherrent_scattering()) rw->set_mu_inc(core->get_incoherrent_scattering(), core->get_incoherrent_scattering_error());
}

QString MainWindow::errors_list()
{
    QString error_line;
    core->setFormula(iw->get_chemicalformula());

    if(!core->is_line_correct())  error_line += "Line incorrect;\t";
    if(iw->get_density() <= 0.0)  error_line += "Density incorrect;\t";
    if(iw->get_lambda() <= 0.0)   error_line += "Lambda incorrect;\t";

    return error_line;
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

    rw = new ResultsWidget();
    iw = new InputWidget();
}

void MainWindow::press_calculate_button()
{
    QString error;
    main_statusbar->showMessage("Calculating...");
    if(errors_list() != "")
        return main_statusbar->showMessage("Error(s): " + errors_list(), 7000);
    if(!core->valid_all())
        error = "There isn't enough data for some calculations.";
    calculation();
    main_statusbar->showMessage("Completed. " + error, 7000);
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

    QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(), filters, &defaultFilter);
}

void MainWindow::help_submenu()
{
    QWidget *frame = new QWidget();
    frame->setGeometry(this->pos().rx(), this->pos().ry(), 602, 974);
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

    this->setWindowTitle("BeeDance");
    this->setCentralWidget(central_widget);

    set_signals();
}

MainWindow::~MainWindow()
{
}
