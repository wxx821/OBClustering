#ifndef IMAGEINFO_H
#define IMAGEINFO_H
#include <QString>

class ImageInfo
{
public:
    ImageInfo();
    ImageInfo(QString in, QString id, QString ifile);
    QString imageName;
    QString imageDecr;
    QString imageFile;
};

#endif // IMAGEINFO_H
