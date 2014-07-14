#ifndef DATATEMPLATE_H
#define DATATEMPLATE_H

#include "ScrDoc.h"
#include "QVector"
#include "attr.h"

class DataTemplate
{
private:
    int getAttrId(QString AttrName);

public:
    DataTemplate();
    void load(CArch& loader);
    void save(CArch& saver);
    void addAttr(QString attrName);
    void addValue(int idAttr, QString valueName);


    int getBitId(QString atrrName, QString valueName);
    int getSize();
    QVector<DataAttr>& getAttributesVector() ;
private:
    int attrCount;
    int size;
    QVector<DataAttr> attributesVector;
    QVector<int> domainLenghtsVector;
    QVector<int> domainAddressVector;
};

#endif // DATATEMPLATE_H
