#include "knowledge.h"

Knowledge::Knowledge()
{
}

void Knowledge::load(CArch& loader) {
    dataTemplate->load(loader);
}

void Knowledge::save(CArch& saver) {
    dataTemplate->save(saver);
}
