#ifndef DATATEMPLATE_H
#define DATATEMPLATE_H

#include "ScrDoc.h"
#include "QVector"

class DataTemplate
{
public:
    DataTemplate();
    void load(CArch& loader);
    void save(CArch& saver);
private:
    int attrCount;
    QVector<CkAttr> attributesVector;
    QVector<int> domainLenghtsVector;
    QVector<int> domainAddressVector;
};

#endif // DATATEMPLATE_H
