#ifndef DATATEMPLATE_H
#define DATATEMPLATE_H

#include "ScrDoc.h"
#include "QVector"
#include "attr.h"

class DataTemplate
{
private:
    int getAttrId(QString attrName);
    DataAttr* getAttr(QString attrName);

public:
    DataTemplate();
    void load(CArch& loader);
    void save(CArch& saver);
    void addAttr(QString attrName);
    void addValue(int idAttr, QString valueName);


    int getBitId(QString attrName, QString valueName);
    int getFirstBitId(QString attrName);
    int getLastBitId(QString attrName);

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
