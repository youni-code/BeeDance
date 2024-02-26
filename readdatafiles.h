#ifndef READDATAFILES_H
#define READDATAFILES_H
#include "element.h"
#include <vector>

class ReadDataFiles
{
private:
    std::vector<Element> set_Elements;

    void readData();
    void writeData(QStringList);
    void show(Element el);

public:
    std::vector<Element> getElements() { return set_Elements; }
    ReadDataFiles();
};

#endif // READDATAFILES_H
