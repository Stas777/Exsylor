#include "modelmanager.h"

ModelManager::ModelManager()
{
}

Model* ModelManager::loadModel(QString &fileName) {
    CArch loader(fileName, 1);
    Model* model = new Model();
    model->load(loader);
    return model;
}


Model* ModelManager::saveModel(QString &fileName) {
    CArch saver(fileName, 1);
    Model* model = new Model();
    model->save(saver);
    return model;
}