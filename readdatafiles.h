#ifndef READDATAFILES_H
#define READDATAFILES_H
#include "element.h"
#include <vector>

class ReadDataFiles
{
private:
    std::vector<Element> elements;

    void readData();
    void writeData(QStringList);
public:
    std::vector<Element> get_elements() { return elements; }
    ReadDataFiles();
};

#endif // READDATAFILES_H
