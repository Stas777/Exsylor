#include "data.h"

Data::Data(DataTemplate* dataTemplate):
    dataTemplate(dataTemplate),
    data((char)0, dataTemplate->getSize()) {}

void Data::load(CArch& loader) {
    dataTemplate->load(loader);
    loader >> data;
}

void Data::save(CArch& saver) {
    dataTemplate->save(saver);
    saver << data;
}

void Data::setAttr(QString attrName, QString valueName) {
    int startBit = dataTemplate->getFirstBitId(attrName);
    int endBit = dataTemplate->getLastBitId(attrName);
    for(int i = startBit; i <= endBit; ++i) {
        data.SetBitAt(i, false);
    }
    int id = dataTemplate->getBitId(attrName, valueName);
    data.SetBitAt(id, true);
}

void Data::setBit(int bitId, bool value) {
    data.SetBitAt(bitId, value);
}

bool Data::getBit(int bitId) {
    return data.GetBitAt(bitId);
}
