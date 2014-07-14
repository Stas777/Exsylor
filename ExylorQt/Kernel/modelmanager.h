#ifndef LOADSAVEMANAGER_H
#define LOADSAVEMANAGER_H

#include <QString>
#include "Model.h"

class Model;

class ModelManager
{
private:
    static Model *model;
public:
    ModelManager();
    static Model* getModel();
    Model* loadModel(QString &fileName);
    void saveModel(QString &fileName, Model& model);
};

#endif // LOADSAVEMANAGER_H
