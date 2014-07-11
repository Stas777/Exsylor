#include "datatemplate.h"

DataTemplate::DataTemplate()
{
}

void DataTemplate::load(CArch& loader) {
    loader >> attrCount;
    for(int i = 0; i < attrCount; i++) {
        CkAttr attr;
        attr.Serialize(loader);
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
    foreach(CkAttr attr, attributesVector) {
        attr.Serialize(saver);
    }
    for(int i = 0; i < attrCount; i++) {
        saver << domainLenghtsVector.at(i);
        saver << domainAddressVector.at(i);
    }
}
