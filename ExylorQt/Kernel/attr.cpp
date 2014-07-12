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
