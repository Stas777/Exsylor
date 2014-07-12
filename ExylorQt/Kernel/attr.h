#ifndef ATTR_H
#define ATTR_H

#include <QString>
#include <QVector>
#include <BaseBool.h>
#include <Archive.h>

class Attr {
public:
    Attr();
    Attr(QString title);
    void addValue(QString valueName);
    virtual void load(CArch& loader); // look up ad ScrObj CkAttr:Serialize
    virtual void save(CArch& saver);
// Attributes
    QString       m_sTitle;     // Name of attribute
    QVector<QString>  m_ValNames;   // Names of attribute values
// Operations
public:

};

class DataAttr : public Attr {
public:
    DataAttr();
    void load(CArch& loader);
    void save(CArch& saver);
private:
    CBV  m_DFlag;               // Attribute values flags
};

class KnowledgAttr : public Attr {
public:
    KnowledgAttr();
    void load(CArch& loader);
    void save(CArch& saver);
private:
    CBV  m_KifFlag;             // Attribute values flags
    CBV  m_KthenFlag;           // Attribute values flags
};

#endif // ATTR_H
