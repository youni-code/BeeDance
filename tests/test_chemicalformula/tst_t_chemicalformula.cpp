#include <QtTest>
#define private public
// #include "../../chemicalformula.h"
// #include "../../simpleformulaelement.h"
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

    void initTestCase();
    void cleanupTestCase();
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


t_chemicalformula::t_chemicalformula() {}

t_chemicalformula::~t_chemicalformula() {}

void t_chemicalformula::initTestCase()
{
}

void t_chemicalformula::cleanupTestCase() {}


QTEST_APPLESS_MAIN(t_chemicalformula)

#include "tst_t_chemicalformula.moc"
