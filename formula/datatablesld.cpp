#include "datatablesld.h"
#include <QFile>



void DataTableSLD::read_data()
{
    QFile file("data/data_sld.txt");

    file.open(QIODevice::ReadOnly | QIODevice::Text); // open file for read like TextFormat
    if(file.atEnd())
        return;
    file.readLine();        // throw out frst line (title)
    while(!file.atEnd())
    {
        QString line(file.readLine());
        line.chop(1);                       // delete last character '\n'
        save_data(line.split('\t'));
    }

    file.close();
}

void DataTableSLD::save_data(QStringList list)
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
    auto sigmaie = list.at(14).toDouble();


    Element temp_element(symb, atom_numb, c_isotop);
    if(list.at(3) != "---")
    {
        temp_element.mass(mass);
    }
    if(list.at(4) != "---")
    {
        temp_element.concentrate(conc);
    }

    if(list.at(5) != "---")
    {
        temp_element.bc_comp(bc);
        temp_element.bc_comp_err(bce);
    }
    if(list.at(7) != "---")
    {
        temp_element.bi_comp(std::complex(rbi,ibi));
        temp_element.bi_comp_err(std::complex(rbie, ibie));
    }
    if(list.at(11) != "---")
    {
        temp_element.sigma_a(sigma);
        temp_element.sigma_a_err(sigmae);
    }
    if(list.at(13) != "---")
    {
        temp_element.sigma_i(sigmai);
        temp_element.sigma_i_err(sigmaie);
    }

    elements.push_back(temp_element);
    // show(temp_element);
    return;
}

DataTableSLD::DataTableSLD()
{
    read_data();
}

Element DataTableSLD::get_element(QString symb, unsigned long nucl) const
{
    for(const auto &it : elements)
        if(it.symbol() == symb && it.nucleons() == nucl)
            return it;
    return Element::Empty();
}
