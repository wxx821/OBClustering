#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QVector>
#include "imageinfo.h"

class DataModel
{
public:
    DataModel();
    QVector<ImageInfo*> iis;
    bool isChanged;
    void addImageInfo(ImageInfo* ii);
    void deleteImageInfo(ImageInfo* ii);
    void deleteImageInfo(QString imageFile);
    ImageInfo* getImageInfo(QString imageFile);
    void clearTemp();
    void emptyData();
};

#endif // DATAMODEL_H
