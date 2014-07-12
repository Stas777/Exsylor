#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include "datatemplate.h"


class Knowledge
{
public:
    Knowledge();
    void load(CArch& loader);
    void save(CArch& saver);
private:
    DataTemplate* dataTemplate;



};

#endif // KNOWLEDGE_H
