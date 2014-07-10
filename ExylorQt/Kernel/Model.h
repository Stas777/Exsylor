#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
    Model();


private:
    QString modelName;
    vector<QString> valueName;
    vector<QString> attribute;
    vector<int> domainAddres;
    vector<int> domainValues;
    DBmap asd ;
};

#endif // MODEL_H
