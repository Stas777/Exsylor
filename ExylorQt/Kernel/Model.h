#pragma once

#include "ScrDoc.h"

#include <QString>

class Model
{
public:
    void load(char* fileName);
    void save(char* fileName);

private:
    QString modelName;

    CkAttrArray attributes;

    QVector<int> domainValues;
    QVector<int> domainAddress;

    CBlockMap knowsMap;
    CBlockMap dataMap;

    QString activeKnowsBlock;
    QString activeDataBlock;
};
