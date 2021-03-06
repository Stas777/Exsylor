#ifndef DATA_H
#define DATA_H

#include "datatemplate.h"
#include "ScrDoc.h"
#include "QVector"
#include "BaseBool.h"

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
    void setAttr(QString attrName, QString valueName);
    bool getBit(int bitId);
private:
    void setBit(int bitId, bool value);




};

#endif // DATA_H
