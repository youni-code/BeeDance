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
    void MainWindow::createstatusbar()
    {
        result_LineEdit->setText("Error!");
        QPalette p;
        p.setColor(QPalette::Base,Qt::red);
        p.setColor(QPalette::Text,Qt::gray);
        main_statusbar->showMessage("Error!", 10000);
        main_statusbar->setPalette(p);
        // result_LineEdit->setPalette(p);
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
        // formula_Label->setText("Hello world");
        formula_Label->setAlignment(Qt::AlignCenter);
        formula_Label->setFont(f);

        formula_TextEdit->setAcceptRichText(false);
        formula_TextEdit->setText("H2ONeCaMgFeCo");
        formula_TextEdit->setMaximumHeight(1.2 * density_LineEdit->height());
        formula_TextEdit->setFont(f);

        density_LineEdit->setValue(1.0);
        density_LineEdit->setSingleStep(0.0002);
        density_LineEdit->setDecimals(8);


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

        density_LineEdit = new QDoubleSpinBox(centralWidget);
        calculate_PushButton = new QPushButton("Run", centralWidget);
        result_LineEdit = new QLineEdit(centralWidget);

        chemicalLayout = new QVBoxLayout(centralWidget);

        chemical_sublayout = new QHBoxLayout();

        main_menubar = new QMenuBar(centralWidget);
        main_statusbar = new QStatusBar(centralWidget);

    }

    void MainWindow::pressCalculateButton()
    {
        main_statusbar->showMessage("Calculating...");

        core->setFormula(formula_TextEdit->toPlainText());
        core->setDensity(density_LineEdit->value());
        double result = core->getResult();
        result_LineEdit->setText(QString::number(result));
        main_statusbar->showMessage("Complited", 5000);

        // calculate_PushButton->setText("isPressed");
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
