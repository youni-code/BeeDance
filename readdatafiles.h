#ifndef READDATAFILES_H
#define READDATAFILES_H
#include "element.h"
#include <vector>
#include <map>

class ReadDataFiles
{
private:
    std::vector<Element> set_Elements;
    std::map<QString, unsigned long> ElemNum;


    void readElements();
    void readIsotopes();
    void readData();

    void writeElement(QStringList);
    void writeIsotopes(QStringList);
    void writeData(QStringList);


public:
    std::vector<Element> getElements() { return set_Elements; }
    std::map<QString, unsigned long> getMap() { return ElemNum; };
    ReadDataFiles();
    Element* findElement(QString, unsigned long = 0);

};

#endif // READDATAFILES_H
