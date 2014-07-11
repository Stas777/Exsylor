#ifndef DATA_H
#define DATA_H

#include "Model.h"
#include "ScrDoc.h"
#include "QVector"

class Data
{
public:
    Data(Model* model);
    void load(CArch& loader);
    void save(CArch& saver);
private:
    Model* model;



};

#endif // DATA_H
