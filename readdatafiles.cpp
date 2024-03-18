#include "readdatafiles.h"
#include <QFile>
#include <QDebug>


void ReadDataFiles::readData()
{
    QFile file("data/data_sld.txt");

    if (!file.exists()) qDebug() << file.fileName() << "File doesn't exist";

    file.open(QIODevice::ReadOnly | QIODevice::Text); // open file for read like TextFormat
    if(file.atEnd()) return;
    file.readLine(); // throw out frst line (title)
    while(!file.atEnd())
    {
        QString line(file.readLine());
        line.chop(1);                       // delete last character '\n'
        writeData(line.split('\t'));
    }

    file.close();

}

void ReadDataFiles::writeData(QStringList list)
{
    auto atom_numb = list.at(0).toULong();
    QString symb = list.at(1);
    auto c_isotop = list.at(2).toULong();
    auto mass= list.at(3).toDouble();
    auto conc = list.at(4).toDouble();

    auto bc= list.at(5).toDouble();
    auto bce= list.at(6).toDouble();

    auto rbi= list.at(7).toDouble();
    auto rbie= list.at(8).toDouble();

    auto ibi= list.at(9).toDouble();
    auto ibie= list.at(10).toDouble();

    auto sigma= list.at(11).toDouble();
    auto sigmae= list.at(12).toDouble();

    auto sigmai = list.at(13).toDouble();


    Element temp_element(symb, atom_numb, c_isotop);
    if(list.at(3) != "---") { temp_element.set_mass(mass); }
    if(list.at(4) != "---") {temp_element.set_concentrate(conc); }

    if(list.at(5) != "---")
    {
        temp_element.set_bc(bc);
        temp_element.set_bc_error(bce);
    }
    if(list.at(7) != "---")
    {
        temp_element.set_bi(std::complex(rbi,ibi));
        temp_element.set_bi_error(std::complex(rbie, ibie));
    }
    if(list.at(11) != "---")
    {
        temp_element.set_sigmaa(sigma);
        temp_element.set_sigmaa_error(sigmae);
    }
    if(list.at(13) != "---")
    {
        temp_element.set_sigmai(sigmai);
    }

    set_Elements.push_back(temp_element);
    // show(temp_element);
    return;
}

void ReadDataFiles::show(Element el)
{
    qDebug() << el.get_symbol() << "\t" << el.get_mass() << "\t" << el.get_bc().real() << "\t" << el.get_bi().real() << " " << el.get_bi().imag() << "i\t";
}



ReadDataFiles::ReadDataFiles()
{
    readData();
}

