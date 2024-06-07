#include "inputwidget.h"

void InputWidget::initialize()
{
    chemical_layout =        new QVBoxLayout();
    formula_TextEdit = new ChemicalTextEdit();
    formula_Label = new ChemicalLabel();

    lamb_dens_sublayout = new QVBoxLayout();
    pushbutton_sublayout = new QHBoxLayout();

    main_sublayout = new QVBoxLayout();
    button_sublayout = new QHBoxLayout();


    density_sublayout =    new QHBoxLayout();
    density_label = new QLabel("Density:");
    density_LineEdit = new QLineEdit();
    density_ComboBox = new QComboBox();

    lambda_sublayout = 	new QHBoxLayout();
    lambda_label = new QLabel("λ:");
    lambda_LineEdit =	new QLineEdit();
    lambda_ComboBox = 	new QComboBox();

    calculate_PushButton = new QPushButton();
}

void InputWidget::set_formulaline()
{
    QFont f = formula_TextEdit->font();
    f.setPointSize(19);

    formula_Label->setFont(f);
    formula_TextEdit->setFont(f);
    formula_TextEdit->setAcceptRichText(false);
    formula_TextEdit->setMaximumHeight(2 * f.pointSize() + 2);
    formula_TextEdit->setPlaceholderText("chemical formula e.g. H2O");
}

void InputWidget::set_densityline()
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

void InputWidget::set_density_lambda_layout()
{
    chemical_layout->addLayout(button_sublayout);
    button_sublayout->addLayout(main_sublayout);

    main_sublayout->addLayout(density_sublayout);
    density_sublayout->addWidget(density_label);
    density_label->setFixedWidth(55);
    density_sublayout->addWidget(density_LineEdit);
    density_sublayout->addWidget(density_ComboBox);
    density_ComboBox->setFixedWidth(70);

    main_sublayout->addLayout(lambda_sublayout);
    lambda_sublayout->addWidget(lambda_label);
    lambda_label->setFixedWidth(55);
    lambda_sublayout->addWidget(lambda_LineEdit);
    lambda_sublayout->addWidget(lambda_ComboBox);
    lambda_ComboBox->setFixedWidth(70);

    button_sublayout->addWidget(calculate_PushButton);
    calculate_PushButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void InputWidget::set_formula_layout()
{
    this->setLayout(chemical_layout);

    chemical_layout->addWidget(formula_TextEdit);
    chemical_layout->addWidget(formula_Label);
    chemical_layout->setAlignment(Qt::AlignTop);
}

void InputWidget::set_signals()
{
    connect(calculate_PushButton, SIGNAL(pressed()),                this,           SIGNAL(push_button()));
    connect(formula_TextEdit,     SIGNAL(changeFormula(QString)),   formula_Label,  SLOT(setFormula(QString)));
    emit formula_TextEdit->changeFormula(formula_TextEdit->toPlainText());
}

InputWidget::InputWidget(QWidget *parent)
    : QWidget{parent}
{
    initialize();
    set_formulaline();
    set_densityline();
    set_formula_layout();
    set_density_lambda_layout();
    set_signals();
}

