#include <QtTest>
#define private public
#include "../../chemicalformula.h"

// add necessary includes here

class t_chemicalformula : public QObject
{
    Q_OBJECT

public:
    t_chemicalformula();
    ~t_chemicalformula();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_brackets_index_inside();
    void test_brackets_inside();
    void test_index_inside();
};

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
    ChemicalFormula a(" ");

    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2^1H2)2Fe2O3")),       "(O2^1H2)2");
    QCOMPARE(a.getLine(a.brackets_index_inside("He2^2H5(O^1H2)2Fe2O3")),            "(O^1H2)2");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2(^1H)2)2Fe2O3")),     "(O2(^1H)2)2");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2(^1H)2)Fe2O3")),      "(O2(^1H)2)");
    QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H52Fe2O3")),               "");
}

void t_chemicalformula::test_brackets_inside()
{
    ChemicalFormula a(" ");

    QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H5(O2^1H2)2Fe2O3")),       "O2^1H2");
    QCOMPARE(a.getLine(a.brackets_inside("He2^2H5(O^1H2)2Fe2O3")),            "O^1H2");
    QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H5(O2(^1H)2)2Fe2O3")),     "O2(^1H)2");
    QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H5(O2(^1H)2)Fe2O3")),      "O2(^1H)2");
    // QCOMPARE(a.getLine(a.brackets_inside("^13CHe2^2H52Fe2O3")),               "");

}

void t_chemicalformula::test_index_inside()
{
    ChemicalFormula a(" ");

    // qDebug() << a.getLine(a.index_inside("^13CHe2^2H5(O2^1H2)2Fe2O3"));
    // QCOMPARE(a.getLine(a.index_inside("^13CHe2^2H5(O2^1H2)2Fe2O3")),       "(O2^1H2)2");
    // QCOMPARE(a.getLine(a.brackets_index_inside("He2^2H5(O^1H2)2Fe2O3")),            "(O^1H2)2");
    // QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2(^1H)2)2Fe2O3")),     "(O2(^1H)2)2");
    // QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H5(O2(^1H)2)Fe2O3")),      "(O2(^1H)2)");
    // QCOMPARE(a.getLine(a.brackets_index_inside("^13CHe2^2H52Fe2O3")),               "");

}

QTEST_APPLESS_MAIN(t_chemicalformula)

#include "tst_t_chemicalformula.moc"
