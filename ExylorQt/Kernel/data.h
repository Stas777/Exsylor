#ifndef DATA_H
#define DATA_H

#include "datatemplate.h"
#include "ScrDoc.h"
#include "QVector"

class Model;

class Data
{
public:
    Data(DataTemplate* dataTemplate);
    void load(CArch& loader);
    void save(CArch& saver);
private:
    DataTemplate* dataTemplate;



};

#endif // DATA_H
