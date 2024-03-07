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

void MainWindow::createmenubar()
{

    QMenu *menu_file = new QMenu("File", main_menubar);
    menu_file->addAction("Open...");
    menu_file->addSeparator();
    menu_file->addAction("Save");
    menu_file->addAction("Save as...");
    menu_file->addSeparator();
    QAction *a = menu_file->addAction("Exit");


    QMenu *menu_help = new QMenu("Help", main_menubar);
    menu_help->addAction("Help...");

    QMenu *menu_view = new QMenu("View");
    menu_view->addAction("Style...");



    main_menubar->addMenu(menu_file);
    main_menubar->addMenu(menu_view);
    main_menubar->addSeparator();
    main_menubar->addMenu(menu_help);

    valid_double = new QDoubleValidator();
    valid_double->setLocale(QLocale::English);

}
void MainWindow::createstatusbar() {  }

void MainWindow::error_message()
{
    result_LineEdit->setText("Error!");
    if(!core->is_line_correct())
        return main_statusbar->showMessage("Error! Something wrong with the input line", 5000);
    if(!core->is_density_correct())
        return main_statusbar->showMessage("Error! Density is wrong ", 5000);
    if(!core->is_all_data_exist())
        return main_statusbar->showMessage("Error! There aren't some elements", 5000);

    return;
}
QWidget* MainWindow::setChemicalLine()
{

    formula_TextEdit->setUndoRedoEnabled(true);


    chemicalLayout->addWidget(formula_TextEdit);
    chemicalLayout->addWidget(formula_Label);

    chemical_sublayout->addWidget(new QLabel("Density:"));
    chemical_sublayout->addWidget(density_LineEdit);
    chemical_sublayout->addStretch(1);
    chemical_sublayout->addWidget(calculate_PushButton);
    chemicalLayout->addLayout(chemical_sublayout);
    chemicalLayout->addStretch(10);

    chemicalLayout->addWidget(result_LineEdit);



    auto f = formula_TextEdit->font();
    f.setPointSize(16);


    connect(formula_TextEdit, SIGNAL(changeFormula(QString)), formula_Label, SLOT(setFormula(QString)));
    //formula_Label->setAlignment(Qt::AlignCenter);
    formula_Label->setFont(f);

    formula_TextEdit->setAcceptRichText(false);
    formula_TextEdit->setText("H2ONeCaMgFeCo");
    formula_TextEdit->setMaximumHeight(1.2 * density_LineEdit->height());
    formula_TextEdit->setFont(f);


    density_LineEdit->setValidator(valid_double);
    density_LineEdit->setText("1.0");

    chemicalLayout->setAlignment(Qt::AlignTop);
    centralWidget->setLayout(chemicalLayout);

    return centralWidget;

}

void MainWindow::setSignals()
{
    connect(calculate_PushButton, SIGNAL(pressed()), this, SLOT(pressCalculateButton()));
}

void MainWindow::initialize()
{
    core = new CoreSLD();

    centralWidget = new QWidget(this);
    formula_TextEdit = new ChemicalTextEdit();
    formula_Label = new ChemicalLabel();

    density_LineEdit = new QLineEdit(centralWidget);
    calculate_PushButton = new QPushButton("Run", centralWidget);
    result_LineEdit = new QLineEdit(centralWidget);
    result_LineEdit->setPlaceholderText("Result");

    chemicalLayout = new QVBoxLayout(centralWidget);

    chemical_sublayout = new QHBoxLayout();

    main_menubar = new QMenuBar(centralWidget);
    main_statusbar = new QStatusBar(centralWidget);

}

QString MainWindow::result_string(double value, double error)
{
    double exp_value = std::floor(std::log10(value));
    double exp_error = std::floor(std::log10(error));

    double min_exp = std::min(exp_value, exp_error);




    qDebug() << exp_value << " " << exp_error;
    qDebug() << value / std::pow(10, min_exp - 1) << " " << error / std::pow(10, min_exp - 1);
    qDebug() << std::round(value / std::pow(10, min_exp - 1)) << " " << std::round(error / std::pow(10, min_exp - 1));

    qDebug() << std::round(value / std::pow(10, min_exp - 1)) * std::pow(10, min_exp - 1);

    auto num = QString::number(std::round(value / std::pow(10, min_exp - 1)) * std::pow(10, min_exp - 1));
    qDebug() << num;
    auto mantisa = num.split('e').first();
    num.removeFirst();
    auto ex = "E" + num.split('e').last();
    if(num.isEmpty()) ex = "";
    auto err = QString::number(std::round(error / std::pow(10, min_exp - 1)));

    // QStringList;
    qDebug() << mantisa + "(" + err + ")" + ex;

    return QString();
}

void MainWindow::pressCalculateButton()
{
    main_statusbar->showMessage("Calculating...");

    core->setFormula(formula_TextEdit->toPlainText());
    core->setDensity(density_LineEdit->text().toDouble());

    if(!core->is_correct())
        return error_message();

    double result = core->get_sld();
    double error = core->get_sld_err();
    result_string(result, error);

    result_LineEdit->setText(QString::number(result) + "±" + QString::number(error));
    main_statusbar->showMessage("Completed", 5000);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initialize();
    createmenubar();
    createstatusbar();
    setChemicalLine();
    this->setWindowTitle("SLD Calculator");
    this->setCentralWidget(centralWidget);

    this->setMenuBar(main_menubar);
    this->setStatusBar(main_statusbar);

    setSignals();
}

MainWindow::~MainWindow()
{
}
