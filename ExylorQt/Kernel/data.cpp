#include "data.h"

Data::Data(DataTemplate* dataTemplate):
    dataTemplate(dataTemplate) {
}

void Data::load(CArch& loader) {
    dataTemplate->load(loader);
    loader >> data;
}

void Data::save(CArch& saver) {
    dataTemplate->save(saver);
    saver << data;
}
