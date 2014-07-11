#ifndef LOADSAVEMANAGER_H
#define LOADSAVEMANAGER_H

#include <QString>
#include <Model.h>

class ModelManager
{
public:
    ModelManager();

    Model* loadModel(QString &fileName);
    Model* saveModel(QString &fileName);
};

#endif // LOADSAVEMANAGER_H
