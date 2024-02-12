#include <QtTest>
#include "../../datatablesld.h"
#include "../../readdatafiles.h"

class t_datatablesld : public QObject
{
    Q_OBJECT

    DataTableSLD *dts;
    ReadDataFiles *rdf;

public:
    t_datatablesld();
    ~t_datatablesld();
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};



t_datatablesld::t_datatablesld()
{

    // Element a = dt->getElement("H", 1);
    // Element a1 = dt->getElement("Ca", 0);
    // ad->getElement("", 1);

}

t_datatablesld::~t_datatablesld()
{
    // DataTableSLD a;
    // ReadDataFiles *file = new ReadDataFiles();
    // dt = new DataTableSLD();
    // dt->setReadData(file);


    // qDebug() << a.getSymbol() << a.getCountNucleons();
    // qDebug() << a1.getSymbol() << a1.getCountNucleons();

}

void t_datatablesld::initTestCase()
{
    QCOMPARE(1, 1);
}

void t_datatablesld::cleanupTestCase()
{
    QCOMPARE(2,2);
}

void t_datatablesld::test_case1()
{
    dts = new DataTableSLD();
    rdf = new ReadDataFiles();

    dts->setReadData(rdf);
    // Element a = ad->getElement("H", 1);
    // qDebug() << a.getSymbol() << a.getCountNucleons();


    // qDebug() << ad->getElement("Fe", 0).getCohb().real();
    // qDebug() << ad->getElement("Fe", 0).getCohb().imag();
    // qDebug() << ad->getElement("Fe", 56).getCohb().real();
    // qDebug() << ad->getElement("Fe", 56).getCohb().imag();

    QCOMPARE(1, 1);
    QCOMPARE(dts->getElement("H", 0).getCohb(), std::complex<double>(-3.7390, 0));
    QCOMPARE(dts->getElement("H", 1).getCohb(), std::complex<double>(-3.7406, 0));

    QCOMPARE(dts->getElement("H", 0).getMass(), 1.00794);

}

QTEST_APPLESS_MAIN(t_datatablesld)
#include "tst_t_datatablesld.moc"
