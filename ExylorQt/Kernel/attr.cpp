#include "attr.h"

Attr::Attr()
{
}

Attr::Attr(QString title) :
    m_sTitle(title){}


void Attr::addValue(QString valueName) {
    m_ValNames.append(valueName);
}

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

int Attr::getValueId(QString valueName) {
    int i = 0;
    foreach (QString name, m_ValNames) {
        if (name == valueName) {
            return i;
        }
        i++;
    }
    return -1;
}

int Attr::getSize() {
    return m_ValNames.size();
}

DataAttr::DataAttr(){
}

DataAttr::DataAttr(QString attrName) :
   Attr(attrName) {}

void DataAttr::load(CArch& loader) {
    Attr::load(loader);
    loader >> m_DFlag;
}
void DataAttr::save(CArch& saver) {
    Attr::save(saver);
    saver << m_DFlag;
}


KnowledgAttr::KnowledgAttr(){
}

KnowledgAttr::KnowledgAttr(QString attrName) :
    Attr(attrName) {}

void KnowledgAttr::load(CArch& loader) {
    Attr::load(loader);
    loader >> m_KifFlag;
    loader >> m_KthenFlag;
}

void KnowledgAttr::save(CArch& saver) {
    Attr::save(saver);
    saver << m_KifFlag;
    saver << m_KthenFlag;
}
