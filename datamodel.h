#ifndef DATAMODEL_H
#define DATAMODEL_H


class DataModel
{
public:
    DataModel();

    bool isChanged;
    void clearTemp();
    void emptyData();
};

#endif // DATAMODEL_H
