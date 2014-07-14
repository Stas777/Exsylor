#include "datatemplate.h"

DataTemplate::DataTemplate() :
    attrCount(0),
    size(0),
    attributesVector(0){}

void DataTemplate::load(CArch& loader) {
    loader >> attrCount;
    for(int i = 0; i < attrCount; i++) {
        DataAttr attr;
        attr.load(loader);
        attributesVector.push_back(attr);
    }
    for(int i = 0; i < attrCount; i++) {
        int domainLenths;
        loader >> domainLenths;
        domainLenghtsVector.push_back(domainLenths);

        int domainAddress;
        loader >> domainAddress;
        domainAddressVector.push_back(domainAddress);
    }
}

QVector<DataAttr>& DataTemplate::getAttributesVector() {
    return attributesVector;
}

void DataTemplate::save(CArch& saver) {
    saver << attrCount;
    foreach(DataAttr attr, attributesVector) {
        attr.save(saver);
    }
    for(int i = 0; i < attrCount; i++) {
        saver << domainLenghtsVector.at(i);
        saver << domainAddressVector.at(i);
    }
}

void DataTemplate::addAttr(QString attrName) {
    attributesVector.push_back(DataAttr(attrName));
}

void DataTemplate::addValue(int idAttr, QString valueName) {
    attributesVector[idAttr].addValue(valueName);
    ++size;
}

int DataTemplate::getAttrId(QString AttrName) {
    int i = 0;
    foreach (DataAttr dataAttr, attributesVector) {
        if (dataAttr.m_sTitle == AttrName) {
            return i;
        }
        ++i;
    }
    return -1;
}

int DataTemplate::getBitId(QString atrrName, QString valueName) {
    DataAttr* dataAttr = &attributesVector[getAttrId(atrrName)];
    int id = dataAttr->getValueId(valueName);
    return id;
}

int DataTemplate::getSize() {
    return size;
}
