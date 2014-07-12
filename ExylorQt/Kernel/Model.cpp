#include "Model.h"
#include "Archive.h"

void Model::load(CArch& loader) {
    loader >> modelName;
    dataTemplate.load(loader);

    foreach(QString k, dataMap.keys())
    {
      loader >> k;
      dataMap.value(k)->load(loader);
    }

    foreach(QString k, knowsMap.keys())
    {
        loader >> k;
        knowsMap.value(k)->load(loader);
    }
}

void Model::save(CArch& saver) {
    saver << modelName;
    dataTemplate.save(saver);

    foreach(QString k, dataMap.keys())
    {
        saver << k;
        dataMap.value(k)->save(saver);
    }

    foreach(QString k, knowsMap.keys())
    {
        saver << k;
        knowsMap.value(k)->save(saver);
    }
}
