#include "modelmanager.h"

ModelManager::ModelManager()
{
}

Model* ModelManager::loadModel(QString &fileName) {
    CArch loader(const_cast<char*>(fileName.toStdString().c_str()), 1);
    Model* model = new Model();
    model->load(loader);
    return model;
}


void ModelManager::saveModel(QString &fileName, Model& model) {
    CArch saver(const_cast<char*>(fileName.toStdString().c_str()), 0);
    model.save(saver);
}
