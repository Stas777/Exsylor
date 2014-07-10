#pragma once

#include "ScrDoc.h"

#include <QString>

class Model
{
public:
    void load(QString fileName);
    void save(QString fileName);

private:
    QString modelName;

    CkAttrArray attributes;

    QVector<int> domainValues;
    QVector<int> domAddress;

    CBlockMap knowsMap;
    CBlockMap dataMap;

    QString activeKnowsBlock;
    QString activeDataBlock;
};
