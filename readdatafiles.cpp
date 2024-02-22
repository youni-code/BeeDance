#include "readdatafiles.h"
#include <QFile>
#include <QDebug>

Element *ReadDataFiles::findElement(QString symb, unsigned long mass)
{
    for(auto it = set_Elements.begin(); it != set_Elements.end(); it++)
    {
        if(it->getSymbol() == symb && it->get_countNucleons() == mass) return &*it;
    }
    return nullptr;
}

void ReadDataFiles::readElements()
{

    QFile file("data/elements.txt");

    if (!file.exists()) qDebug() << file.fileName() << "File doesn't exist";


    file.open(QIODevice::ReadOnly | QIODevice::Text); // open file for read like TextFormat
    if(file.atEnd()) return;
    file.readLine(); // throw out title
    while(!file.atEnd())
    {
        QString line(file.readLine());
        line.chop(1);                       // delete last character '\n'
        writeElement(line.split('\t'));
    }
    file.close();
}

void ReadDataFiles::readIsotopes()
{
    QFile file("data/isotopes.txt");

    if (!file.exists()) qDebug() << file.fileName() << "File doesn't exist";


    file.open(QIODevice::ReadOnly | QIODevice::Text); // open file for read like TextFormat
    if(file.atEnd()) return;
    file.readLine(); // throw out frst line (title)
    while(!file.atEnd())
    {
        QString line(file.readLine());
        line.chop(1);                       // delete last character '\n'
        writeIsotopes(line.split('\t'));
    }
    file.close();

}

void ReadDataFiles::readData()
{
    QFile file("data/sld_data.txt");

    if (!file.exists()) qDebug() << file.fileName() << "File doesn't exist";

    file.open(QIODevice::ReadOnly | QIODevice::Text); // open file for read like TextFormat
    if(file.atEnd()) return;
    file.readLine(); // throw out frst line (title)
    while(!file.atEnd())
    {
        QString line(file.readLine());
        line.chop(1);                       // delete last character '\n'
        writeData(line.split('\t'));
        // qDebug() << line.split('\t');
        // writeIsotopes(line.split('\t'));
    }
    file.close();

}

void ReadDataFiles::readData2()
{
    QFile file("data/sld_data2.txt");

    if (!file.exists()) qDebug() << file.fileName() << "File doesn't exist";

    file.open(QIODevice::ReadOnly | QIODevice::Text); // open file for read like TextFormat
    if(file.atEnd()) return;
    file.readLine(); // throw out frst line (title)
    while(!file.atEnd())
    {
        QString line(file.readLine());
        line.chop(1);                       // delete last character '\n'
        auto l = line.split('\t')[0];
        qDebug() << l;
        l = line.split('\t')[1];
        qDebug() << l;
        l = line.split('\t')[2];
        qDebug() << l;
        l = line.split('\t')[3];
        qDebug() << l;
        // writeData(line.split('\t'));
        // qDebug() << line.split('\t');
        // writeIsotopes(line.split('\t'));
    }
    file.close();

}

void ReadDataFiles::writeElement(QStringList list_e)
{
    Element el(list_e.at(1), list_e.at(0).toULong());
    if(list_e.at(2) != "---") el.set_mass(list_e.at(2).toDouble());

    ElemNum.insert(std::pair<QString, unsigned long>(list_e.at(1), list_e.at(0).toULong()));
    return set_Elements.push_back(el);
}

void ReadDataFiles::writeIsotopes(QStringList list_i)
{
    Element el(list_i.at(0), ElemNum[list_i.at(0)], list_i.at(1).toULong());
    if(list_i.at(2) != "---") el.set_mass(list_i.at(2).toDouble());

    return set_Elements.push_back(el);
}

void ReadDataFiles::writeData(QStringList list_d)
{
    QString symb = list_d.at(1);

    unsigned long count_isot = 0;
    double conc = 0.0;

    double cohb_real = 0.0;
    double cohb_im = 0.0;

    double inc_real = 0.0;
    double inc_im = 0.0;

    double cohxs = 0.0;
    double incxs = 0.0;

    if(list_d.at(2) != "---") count_isot = list_d.at(2).toULong();
    if(list_d.at(3) != "---") conc = list_d.at(3).toDouble();

    if(list_d.at(5) != "---") cohb_real = list_d.at(5).toDouble();
    if(list_d.at(6) != "---") cohb_im = list_d.at(6).toDouble();

    if(list_d.at(8) != "---") inc_real = list_d.at(8).toDouble();
    if(list_d.at(9) != "---") inc_im = list_d.at(9).toDouble();

    if(list_d.at(10) != "---") cohxs = list_d.at(10).toDouble();
    if(list_d.at(11) != "---") incxs = list_d.at(11).toDouble();


    auto find_elem = findElement(symb, count_isot);
    if(find_elem == nullptr)
    {

        qDebug() << "Not found: " << symb << count_isot;
        return;
    }
    find_elem->set_concentrate(conc);
    find_elem->set_bc(std::complex<double>(cohb_real, cohb_im));
    find_elem->set_bi(std::complex<double>(inc_real, inc_im));
    find_elem->setCohxs(cohxs);
    find_elem->setIncxs(incxs);
}



ReadDataFiles::ReadDataFiles()
{
    readElements();
    // qDebug() << "ElemNum size: " << ElemNum.size();
    // qDebug() << "ElemNum Na: " << ElemNum["Na"];
    readIsotopes();
    readData();
    readData2();

    // for(auto it = set_Elements.begin(); it != set_Elements.end(); it++)
    //     qDebug() << it->getSymbol() << it->getAtomicNumber() << it->getCountNucleons();
    qDebug() << "Finish reading";
}

