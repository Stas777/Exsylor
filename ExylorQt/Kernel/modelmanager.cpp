#include "modelmanager.h"

ModelManager::ModelManager()
{
    model = null;
}

Model* ModelManager::getModel(){
    if(model == null){
        model = new Model();
    }
    return model;
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
