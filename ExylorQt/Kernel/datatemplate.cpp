#include "datatemplate.h"

DataTemplate::DataTemplate() :
    attrCount(0),
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
}
