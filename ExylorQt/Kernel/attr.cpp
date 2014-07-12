#include "attr.h"

Attr::Attr()
{
}

Attr::Attr(QString title) :
    m_sTitle(title){}


void Attr::addValue(QString valueName) {
    m_ValNames.append(valueName);
}

DataAttr::DataAttr(QString attrName) :
    Attr(attrName) {}

void Attr::load(CArch& loader) {
    loader >> m_sTitle;
    int valCount;
    loader >> valCount;
    for(int i = 0; i < valCount; i++) {
        QString valName;
        loader >> valName;
        m_ValNames.push_back(valName);
    }
}

void Attr::save(CArch& saver) {
    saver << m_sTitle;
    saver << m_ValNames.size();
    foreach(QString qstr, m_ValNames) {
        saver << qstr;
    }
}

void DataAttr::load(CArch& loader) {
    Attr::load(loader);
    int bitCount;
    load >> bitCount;
}

void DataAttr::save(CArch& saver) {
    Attr::save(saver);
}
