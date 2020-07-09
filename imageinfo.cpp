#include "imageinfo.h"

ImageInfo::ImageInfo()
{
    this->imageName = "";
    this->imageDecr = "";
    this->imageFile = "";
}

ImageInfo::ImageInfo(QString in, QString id, QString ifile){
    this->imageName = in;
    this->imageDecr = id;
    this->imageFile = ifile;
}
