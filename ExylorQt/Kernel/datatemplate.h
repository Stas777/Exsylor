#ifndef DATATEMPLATE_H
#define DATATEMPLATE_H

#include "ScrDoc.h"
#include "QVector"
#include "attr.h"

class DataTemplate
{
public:
    DataTemplate();
    void load(CArch& loader);
    void save(CArch& saver);
    void addAttr(QString attrName);
    void addValue(int idAttr, QString valueName);
private:
    int attrCount;
    QVector<DataAttr> attributesVector;
    QVector<int> domainLenghtsVector;
    QVector<int> domainAddressVector;
};

#endif // DATATEMPLATE_H
