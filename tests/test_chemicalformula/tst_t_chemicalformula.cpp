#include <QtTest>
#define private public
#include "../../chemicalformula.h"
#include "../../simpleformulaelement.h"
#include "../../formula.h"

// add necessary includes here

class t_chemicalformula : public QObject
{
    Q_OBJECT

public:
    t_chemicalformula();
    ~t_chemicalformula();

private slots:
    void test_remove_int_value();
    void test_remove_element_name();
    void test_remove_double_index();

    void test_remove_element();
    void test_remove_open_bracket();
    void test_remove_close_bracket_index();
    void test_remove_square_brackets();
    void test_add_line();



    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_brackets_index_inside();
    void test_brackets_inside();
    void test_readIsotope1();
    void test_readIsotope2();
    void get_index();
    void get_firstElement();
    void del_firstElement();

    void is_multiformula();
    // void check_roundbrackets();
    // void check_format();
    // void is_correct();

    void test_formula_add();



    void getElements();
};

void t_chemicalformula::test_remove_int_value()
{
    Formula formula;

    QString str = "Fe()";
    QString str1 = "23";
    QString str2 = "22.3";
    QString str3 = "3Fe";
    QString str4 = "InFeTeO6";
    QString str5 = "3333";
    QString str6 = "101In";
    QString str7 = ")))";
    QString str8 = "(((";
    QString str9 = "268";
    QString str10 = "FeeeF";

    QCOMPARE(formula.remove_int_value(str), "");
    QCOMPARE(formula.remove_int_value(str1), "23");
    QCOMPARE(formula.remove_int_value(str2), "22");
    QCOMPARE(formula.remove_int_value(str3), "3");
    QCOMPARE(formula.remove_int_value(str4), "");
    QCOMPARE(formula.remove_int_value(str5), "3333");
    QCOMPARE(formula.remove_int_value(str6), "101");
    QCOMPARE(formula.remove_int_value(str7), "");
    QCOMPARE(formula.remove_int_value(str8), "");
    QCOMPARE(formula.remove_int_value(str9), "268");
    QCOMPARE(formula.remove_int_value(str10), "");

    QCOMPARE(str, "Fe()");
    QCOMPARE(str1, "");
    QCOMPARE(str2, ".3");
    QCOMPARE(str3, "Fe");
    QCOMPARE(str4, "InFeTeO6");
    QCOMPARE(str5, "");
    QCOMPARE(str6, "In");
    QCOMPARE(str7, ")))");
    QCOMPARE(str8, "(((");
    QCOMPARE(str9, "");
    QCOMPARE(str10, "FeeeF");


}

void t_chemicalformula::test_remove_element_name()
{
    Formula formula;

    QString str =   "Fe()";
    QString str1 =  "23";
    QString str2 =  "22.3";
    QString str3 =  "3Fe";
    QString str4 =  "InFeTeO6";
    QString str5 =  "3333";
    QString str6 =  "101In";
    QString str7 =  "32.3";
    QString str8 =  "(((";
    QString str9 =  "268";
    QString str10 = "FeeeT";

    QCOMPARE(formula.remove_element_name(str),   "Fe");
    QCOMPARE(formula.remove_element_name(str1),  "");
    QCOMPARE(formula.remove_element_name(str2),  "");
    QCOMPARE(formula.remove_element_name(str3),  "");
    QCOMPARE(formula.remove_element_name(str4),  "In");
    QCOMPARE(formula.remove_element_name(str5),  "");
    QCOMPARE(formula.remove_element_name(str6),  "");
    QCOMPARE(formula.remove_element_name(str7),  "");
    QCOMPARE(formula.remove_element_name(str8),  "");
    QCOMPARE(formula.remove_element_name(str9),  "");
    QCOMPARE(formula.remove_element_name(str10), "Feee");

    QCOMPARE(str, "()");
    QCOMPARE(str1, "23");
    QCOMPARE(str2, "22.3");
    QCOMPARE(str3, "3Fe");
    QCOMPARE(str4, "FeTeO6");
    QCOMPARE(str5, "3333");
    QCOMPARE(str6, "101In");
    QCOMPARE(str7, "32.3");
    QCOMPARE(str8, "(((");
    QCOMPARE(str9, "268");
    QCOMPARE(str10, "T");

}

void t_chemicalformula::test_remove_double_index()
{
    Formula formula;

    QString str =   "Fe()";
    QString str1 =  "23";
    QString str2 =  "22.3";
    QString str3 =  "3Fe";
    QString str4 =  "InFeTeO6";
    QString str5 =  "3333";
    QString str6 =  "101In";
    QString str7 =  "32.3";
    QString str8 =  "(((";
    QString str9 =  "268";
    QString str10 = "FeeeF";

    QCOMPARE(formula.remove_double_index(str),   "");
    QCOMPARE(formula.remove_double_index(str1),  "23");
    QCOMPARE(formula.remove_double_index(str2),  "22.3");
    QCOMPARE(formula.remove_double_index(str3),  "3");
    QCOMPARE(formula.remove_double_index(str4),  "");
    QCOMPARE(formula.remove_double_index(str5),  "3333");
    QCOMPARE(formula.remove_double_index(str6),  "101");
    QCOMPARE(formula.remove_double_index(str7),  "32.3");
    QCOMPARE(formula.remove_double_index(str8),  "");
    QCOMPARE(formula.remove_double_index(str9),  "268");
    QCOMPARE(formula.remove_double_index(str10), "");

    QCOMPARE(str, "Fe()");
    QCOMPARE(str1, "");
    QCOMPARE(str2, "");
    QCOMPARE(str3, "Fe");
    QCOMPARE(str4, "InFeTeO6");
    QCOMPARE(str5, "");
    QCOMPARE(str6, "In");
    QCOMPARE(str7, "");
    QCOMPARE(str8, "(((");
    QCOMPARE(str9, "");
    QCOMPARE(str10, "FeeeF");

}

void t_chemicalformula::test_remove_element()
{
    Formula formula;

    QString str =   "Fe()";
    QString str1 =  "23";
    QString str2 =  "22.3";
    QString str3 =  "^3Fe3";
    QString str4 =  "InFeTeO6";
    QString str5 =  "3333";
    QString str6 =  "101In";
    QString str7 =  "32.3";
    QString str8 =  "(((";
    QString str9 =  "268";
    QString str10 = "Feee2F";

    QCOMPARE(formula.remove_element(str),   "Fe");
    QCOMPARE(formula.remove_element(str1),  "");
    QCOMPARE(formula.remove_element(str2),  "");
    QCOMPARE(formula.remove_element(str3),  "^3Fe3");
    QCOMPARE(formula.remove_element(str4),  "In");
    QCOMPARE(formula.remove_element(str5),  "");
    QCOMPARE(formula.remove_element(str6),  "");
    QCOMPARE(formula.remove_element(str7),  "");
    QCOMPARE(formula.remove_element(str8),  "");
    QCOMPARE(formula.remove_element(str9),  "");
    QCOMPARE(formula.remove_element(str10), "Feee2");

    QCOMPARE(str, "()");
    QCOMPARE(str1, "23");
    QCOMPARE(str2, "22.3");
    QCOMPARE(str3, "");
    QCOMPARE(str4, "FeTeO6");
    QCOMPARE(str5, "3333");
    QCOMPARE(str6, "101In");
    QCOMPARE(str7, "32.3");
    QCOMPARE(str8, "(((");
    QCOMPARE(str9, "268");
    QCOMPARE(str10, "F");

}

void t_chemicalformula::test_remove_open_bracket()
{
    Formula formula;

    QString str =   "Fe()";
    QString str1 =  "23";
    QString str2 =  "22.3";
    QString str3 =  "3Fe";
    QString str4 =  "InFeTeO6";
    QString str5 =  "3333";
    QString str6 =  "101In";
    QString str7 =  "32.3";
    QString str8 =  "(((";
    QString str9 =  "268";
    QString str10 = "FeeeF";

    QCOMPARE(formula.remove_open_bracket(str),   "");
    QCOMPARE(formula.remove_open_bracket(str1),  "");
    QCOMPARE(formula.remove_open_bracket(str2),  "");
    QCOMPARE(formula.remove_open_bracket(str3),  "");
    QCOMPARE(formula.remove_open_bracket(str4),  "");
    QCOMPARE(formula.remove_open_bracket(str5),  "");
    QCOMPARE(formula.remove_open_bracket(str6),  "");
    QCOMPARE(formula.remove_open_bracket(str7),  "");
    QCOMPARE(formula.remove_open_bracket(str8),  "(");
    QCOMPARE(formula.remove_open_bracket(str9),  "");
    QCOMPARE(formula.remove_open_bracket(str10), "");

    QCOMPARE(str, "Fe()");
    QCOMPARE(str1, "23");
    QCOMPARE(str2, "22.3");
    QCOMPARE(str3, "3Fe");
    QCOMPARE(str4, "InFeTeO6");
    QCOMPARE(str5, "3333");
    QCOMPARE(str6, "101In");
    QCOMPARE(str7, "32.3");
    QCOMPARE(str8, "((");
    QCOMPARE(str9, "268");
    QCOMPARE(str10, "FeeeF");

}

void t_chemicalformula::test_remove_close_bracket_index()
{
    Formula formula;

    QString str =   ")33.3(";
    QString str1 =  "Fe";
    QString str2 =  "))";
    QString str3 =  "3Fe";
    QString str4 =  "InFeTeO6";
    QString str5 =  "3333";
    QString str6 =  "101In";
    QString str7 =  "32.3";
    QString str8 =  "(((";
    QString str9 =  "268";
    QString str10 = "FeeeF";
    QString str11 = ")3..3";

    QCOMPARE(formula.remove_close_bracket_index(str),   ")33.3");
    QCOMPARE(formula.remove_close_bracket_index(str1),  "");
    QCOMPARE(formula.remove_close_bracket_index(str2),  ")");
    QCOMPARE(formula.remove_close_bracket_index(str3),  "");
    QCOMPARE(formula.remove_close_bracket_index(str4),  "");
    QCOMPARE(formula.remove_close_bracket_index(str5),  "");
    QCOMPARE(formula.remove_close_bracket_index(str6),  "");
    QCOMPARE(formula.remove_close_bracket_index(str7),  "");
    QCOMPARE(formula.remove_close_bracket_index(str8),  "");
    QCOMPARE(formula.remove_close_bracket_index(str9),  "");
    QCOMPARE(formula.remove_close_bracket_index(str10), "");
    QCOMPARE(formula.remove_close_bracket_index(str11), ")");

    QCOMPARE(str, "(");
    QCOMPARE(str1, "Fe");
    QCOMPARE(str2, ")");
    QCOMPARE(str3, "3Fe");
    QCOMPARE(str4, "InFeTeO6");
    QCOMPARE(str5, "3333");
    QCOMPARE(str6, "101In");
    QCOMPARE(str7, "32.3");
    QCOMPARE(str8, "(((");
    QCOMPARE(str9, "268");
    QCOMPARE(str10, "FeeeF");

}

void t_chemicalformula::test_remove_square_brackets()
{
    Formula formula;

    QString str =   "[3.3]Al";
    QString str1 =  "Fe";
    QString str2 =  "[]))";
    QString str3 =  "3Fe";
    QString str4 =  "][";

    QString str5 =  "[Fe]";
    QString str6 =  "101In";
    QString str7 =  "32.3";
    QString str8 =  "(((";
    QString str9 =  "[268]";
    QString str10 = "FeeeF";
    QString str11 = "[33Fe3";

    QCOMPARE(formula.remove_square_brackets(str),   "[3.3]");
    QCOMPARE(formula.remove_square_brackets(str1),  "");
    QCOMPARE(formula.remove_square_brackets(str2),  "");
    QCOMPARE(formula.remove_square_brackets(str3),  "");
    QCOMPARE(formula.remove_square_brackets(str4),  "");
    QCOMPARE(formula.remove_square_brackets(str5),  "");
    QCOMPARE(formula.remove_square_brackets(str6),  "");
    QCOMPARE(formula.remove_square_brackets(str7),  "");
    QCOMPARE(formula.remove_square_brackets(str8),  "");
    QCOMPARE(formula.remove_square_brackets(str9),  "[268]");
    QCOMPARE(formula.remove_square_brackets(str10), "");
    QCOMPARE(formula.remove_square_brackets(str11), "");

    QCOMPARE(str, "Al");
    QCOMPARE(str1, "Fe");
    QCOMPARE(str2, "[]))");
    QCOMPARE(str3, "3Fe");
    QCOMPARE(str4, "][");
    QCOMPARE(str5, "[Fe]");
    QCOMPARE(str6, "101In");
    QCOMPARE(str7, "32.3");
    QCOMPARE(str8, "(((");
    QCOMPARE(str9, "");
    QCOMPARE(str10, "FeeeF");
    QCOMPARE(str11, "[33Fe3");

}

void t_chemicalformula::test_add_line()
{

}

t_chemicalformula::t_chemicalformula() {}

t_chemicalformula::~t_chemicalformula() {}

void t_chemicalformula::initTestCase()
{
}

void t_chemicalformula::cleanupTestCase() {}

void t_chemicalformula::test_case1()
{
    QCOMPARE(1, 1);
}

void t_chemicalformula::test_brackets_index_inside()
{
    ChemicalFormula a;

    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2^1H2)2Fe2O3")),       "(O2^1H2)2");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2^1H2)2Fe2O3")),       "(O2^1H2)2");
    QCOMPARE(a.getLine(a.brackets_index_inside("He2^2H5(O^1H2)2Fe2O3")),            "(O^1H2)2");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2(^1H)2)2Fe2O3")),     "(O2(^1H)2)2");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2(^1H)2)Fe2O3")),      "(O2(^1H)2)");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2(^1H)2)Fe2O3")),      "(O2(^1H)2)");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H52Fe2O3")),               "");
}

void t_chemicalformula::test_brackets_inside()
{
    ChemicalFormula a;

    QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H5(O2^1H2)2Fe2O3")),       "O2^1H2");
    QCOMPARE(a.getLine(a.brackets_inside("He2^2H5(O^1H2)2Fe2O3")),            "O^1H2");
    QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H5(O2(^1H)2)2Fe2O3")),     "O2(^1H)2");
    QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H5(O2(^1H)2)Fe2O3")),      "O2(^1H)2");
    QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H52Fe2O3")),               "");

}


void t_chemicalformula::test_readIsotope1()
{
    ChemicalFormula cf;

    QCOMPARE(cf.readIsotope("^2H2"),            SimpleFormulaElement("H", 2));
    QCOMPARE(cf.readIsotope("^2H2"),            SimpleFormulaElement("H", 2));
    QCOMPARE(cf.readIsotope("^22Fe2"),          SimpleFormulaElement("Fe", 22));
    QCOMPARE(cf.readIsotope("^222Te"),          SimpleFormulaElement("Te", 222));
    QCOMPARE(cf.readIsotope("^123O2"),          SimpleFormulaElement("O", 123));
    QCOMPARE(cf.readIsotope("^123Ohra.2"),       SimpleFormulaElement("Ohra", 123));
    QCOMPARE(cf.readIsotope("O0.33"),               SimpleFormulaElement("O"));
    QCOMPARE(cf.readIsotope("O3"),               SimpleFormulaElement("O"));
    QCOMPARE(cf.readIsotope("O4"),               SimpleFormulaElement("O", 0));
    QCOMPARE(cf.readIsotope(""),                SimpleFormulaElement(""));
}

void t_chemicalformula::test_readIsotope2()
{
    ChemicalFormula cf("");

    QCOMPARE(cf.readIsotope("^2H").index_,               1);
    QCOMPARE(cf.readIsotope("^2H2").index_,              2);
    QCOMPARE(cf.readIsotope("^22Fe2").index_,            2);
    QCOMPARE(cf.readIsotope("^222Te").index_,            1);
    QCOMPARE(cf.readIsotope("^123O2").index_,            2);
    QCOMPARE(cf.readIsotope("^123Ohra.2").index_,        0.2);
    QCOMPARE(cf.readIsotope("O0.33").index_,             .33);
    QCOMPARE(cf.readIsotope("").index_,                  0.0);

}

void t_chemicalformula::get_index()
{
    ChemicalFormula a("");

    QCOMPARE((a.get_index("(O2^1H2)2")), 2);
    QCOMPARE((a.get_index("(O^1H2).2")),       0.2);
    QCOMPARE((a.get_index("(O2(^1H)2)2.2")), 2.2);
    QCOMPARE((a.get_index("(O2^1H2)")), 1);
    QCOMPARE((a.get_index("He")), 0);
    QCOMPARE((a.get_index("H")), 0);
    QCOMPARE((a.get_index("")), 0);
}

void t_chemicalformula::get_firstElement()
{
    ChemicalFormula cf("");

    QCOMPARE(cf.get_firstElement("^2H2"),            SimpleFormulaElement("H", 2));
    QCOMPARE(cf.get_firstElement("^2H2"),            SimpleFormulaElement("H", 2));
    QCOMPARE(cf.get_firstElement("^22Fe2"),          SimpleFormulaElement("Fe", 22));
    QCOMPARE(cf.get_firstElement("^222Te"),          SimpleFormulaElement("Te", 222));
    QCOMPARE(cf.get_firstElement("^123O2"),          SimpleFormulaElement("O", 123));
    QCOMPARE(cf.get_firstElement("^123Ohra.2"),       SimpleFormulaElement("Ohra", 123));
    QCOMPARE(cf.get_firstElement("O0.33"),               SimpleFormulaElement("O"));
    QCOMPARE(cf.get_firstElement("O3"),               SimpleFormulaElement("O"));
    QCOMPARE(cf.get_firstElement("O4"),               SimpleFormulaElement("O", 0));
    QCOMPARE(cf.get_firstElement("^2H2Te2O5"),            SimpleFormulaElement("H", 2));
    QCOMPARE(cf.get_firstElement("^2H2^23Si"),            SimpleFormulaElement("H", 2));
    QCOMPARE(cf.get_firstElement("^22Fe2Fe"),          SimpleFormulaElement("Fe", 22));
    QCOMPARE(cf.get_firstElement("^222Te^2Fe"),          SimpleFormulaElement("Te", 222));
    QCOMPARE(cf.get_firstElement("^123O2"),          SimpleFormulaElement("O", 123));
    QCOMPARE(cf.get_firstElement("^123Ohra.2"),       SimpleFormulaElement("Ohra", 123));
    QCOMPARE(cf.get_firstElement("O0.33"),               SimpleFormulaElement("O"));
    QCOMPARE(cf.get_firstElement("O3"),               SimpleFormulaElement("O"));
    QCOMPARE(cf.get_firstElement("O4"),               SimpleFormulaElement("O", 0));
    QCOMPARE(cf.get_firstElement("OH"),               SimpleFormulaElement("O", 0));
    QCOMPARE(cf.get_firstElement(""),                SimpleFormulaElement(""));

}

void t_chemicalformula::del_firstElement()
{
    ChemicalFormula cf("");

    QCOMPARE(cf.del_firstElement("^2H2"),            "");
    QCOMPARE(cf.del_firstElement("^2H2"),            "");
    QCOMPARE(cf.del_firstElement("^22Fe2"),          "");
    QCOMPARE(cf.del_firstElement("^222Te"),          "");
    QCOMPARE(cf.del_firstElement("^123O2"),          "");
    QCOMPARE(cf.del_firstElement("^123Ohra.2"),      "");
    QCOMPARE(cf.del_firstElement("O0.33"),           "");
    QCOMPARE(cf.del_firstElement("O3"),              "");
    QCOMPARE(cf.del_firstElement("O4"),              "");
    QCOMPARE(cf.del_firstElement("^2H2Te2O5"),       "Te2O5");
    QCOMPARE(cf.del_firstElement("^2H2^23Si"),       "^23Si");
    QCOMPARE(cf.del_firstElement("^22Fe2Fe"),        "Fe");
    QCOMPARE(cf.del_firstElement("^222Te^2Fe"),      "^2Fe");
    QCOMPARE(cf.del_firstElement("^123O2"),          "");
    QCOMPARE(cf.del_firstElement("^123Ohra.2"),      "");
    QCOMPARE(cf.del_firstElement("O0.33"),           "");
    QCOMPARE(cf.del_firstElement("O3"),              "");
    QCOMPARE(cf.del_firstElement("O4"),              "");
    QCOMPARE(cf.del_firstElement("OH"),              "H");
    QCOMPARE(cf.del_firstElement("H"),              "");
    QCOMPARE(cf.del_firstElement(""),                "");

}

void t_chemicalformula::is_multiformula()
{
    ChemicalFormula cf;
    QCOMPARE(cf.is_multiformula("^2H2"),            false);
    QCOMPARE(cf.is_multiformula("H2O"),             false);
    QCOMPARE(cf.is_multiformula("H2O[2]"),          true);
}

void t_chemicalformula::test_formula_add()
{


}


// void t_chemicalformula::check_roundbrackets()
// {
//     ChemicalFormula cf;
//     QCOMPARE(cf.check_roundbrackets("2H2"), true);
//     QCOMPARE(cf.check_roundbrackets("(2H2"), false);
//     QCOMPARE(cf.check_roundbrackets("(2H2)"), true);
//     QCOMPARE(cf.check_roundbrackets("(2H)2"), true);
//     QCOMPARE(cf.check_roundbrackets("(2H2)"), true);
//     QCOMPARE(cf.check_roundbrackets("(2(H2)"), false);
//     QCOMPARE(cf.check_roundbrackets("()(2H2)"), true);
//     QCOMPARE(cf.check_roundbrackets("((2H2)"), false);
//     QCOMPARE(cf.check_roundbrackets("((2H2))"), true);
//     QCOMPARE(cf.check_roundbrackets("()(2H)2"), true);
//     QCOMPARE(cf.check_roundbrackets("(2H2))"), false);
//     QCOMPARE(cf.check_roundbrackets("((2H2))"), true);
// }

// void t_chemicalformula::check_format()
// {
//     ChemicalFormula cf;
//     // QCOMPARE(cf.check_format("[3]"), true);
//     // QCOMPARE(cf.check_format("[3.3][3]"), true);
//     // QCOMPARE(cf.check_format("[][3]"), false);
//     // QCOMPARE(cf.check_format("[.][90.334]"), false);
//     // QCOMPARE(cf.check_format("[3.][3]"), true);
//     // QCOMPARE(cf.check_format("[3.33][.3]"), true);


//     QCOMPARE(cf.check_format("^2H2OHe"), true);
//     QCOMPARE(cf.check_format("(^2H2^34O)2He"), true);

// }

// void t_chemicalformula::is_correct()
// {
//     ChemicalFormula cf;
//     QCOMPARE(cf.is_correct(""), false);
//     QCOMPARE(cf.is_correct("H2O"), true);
//     QCOMPARE(cf.is_correct("H2[3]O"), false);
//     QCOMPARE(cf.is_correct("H2[3]O[3]"), true);
//     QCOMPARE(cf.is_correct("H2O[3]"), true);

// }

void t_chemicalformula::getElements()
{
    ChemicalFormula cf;
    auto res = cf.getElements("(^13C2He2^2H5((O2).2^1H2)2Fe2O3)2");
    // for(auto it(res.begin()); it != res.end(); it++) qDebug() << it->symbol() << "(" << it->nucleons() << ", " << it->index() << ")";

}

////////////////////////////////////////////^13CHe2^2H5(O2^1H2)2Fe2O3
QTEST_APPLESS_MAIN(t_chemicalformula)

#include "tst_t_chemicalformula.moc"
