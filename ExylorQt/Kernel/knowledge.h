#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include "Model.h"

class Knowledge
{
public:
    Knowledge();
    void load(CArch& loader);
    void save(CArch& saver);
private:
    Model* model;



};

#endif // KNOWLEDGE_H
