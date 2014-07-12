#ifndef DATA_H
#define DATA_H

#include "datatemplate.h"
#include "ScrDoc.h"
#include "QVector"
#include "BaseBool.h"

class Model;

class Data
{
public:
    Data(DataTemplate* dataTemplate);
    void load(CArch& loader);
    void save(CArch& saver);
private:
    DataTemplate* dataTemplate;
    CBV data;
public:





};

#endif // DATA_H
