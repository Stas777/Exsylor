#pragma once

#include "ScrDoc.h"

#include <QString>
#include <QMap>
#include "data.h"
#include "knowledge.h"
#include "datatemplate.h"
#include "modelmanager.h"
#include "Archive.h"

class Model {

friend class ModelManager;

public:
    Model();

    void load(CArch& loader);
    void save(CArch& saver);

    DataTemplate* getDataTemplate();
    void setDataTemplate(const DataTemplate &value);

private:
    QString modelName;

    DataTemplate dataTemplate;

    QMap<QString, Data*> dataMap;
    QMap<QString, Knowledge*> knowsMap;
};
