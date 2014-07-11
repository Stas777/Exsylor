#include "Model.h"
#include "Archive.h"

void Model::load(CArch& loader) {
    loader >> activeDataBlock;
    loader >> activeKnowsBlock;
    attributes.Serialize(loader);
    knowsMap.Serialize(archive);
    dataMap.Serialize(archive);
}

void Model::save(CArch& saver) {
    saver << modelName;
    dataTemplate.save(saver);

    attributes.Serialize(saver);
    knowsMap.Serialize(archive);
    dataMap.Serialize(archive);
}
