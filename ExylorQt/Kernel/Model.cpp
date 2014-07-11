#include "Model.h"
#include "Archive.h"

void Model::load(char* fileName) {
    CArch archive(fileName, 1);
    //WORD N;
    //archive >> N;
    //archive >> N;
    //m_nAttributes = N;
    //m_nValues = N;
    archive >> activeDataBlock;
    archive >> activeKnowsBlock;
    attributes.Serialize(archive);
    knowsMap.Serialize(archive);
    dataMap.Serialize(archive);
}

void Model::save(char* fileName) {
    CArch archive(fileName, 0);
    //archive << (WORD)m_nAttributes;
    //archive << (WORD)m_nValues;
    archive << activeDataBlock;
    archive << activeKnowsBlock;
    attributes.Serialize(archive);
    knowsMap.Serialize(archive);
    dataMap.Serialize(archive);
}
