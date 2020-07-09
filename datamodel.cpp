#include "datamodel.h"

DataModel::DataModel()
{
    this->isChanged = false;
}

void DataModel::addImageInfo(ImageInfo* ii){
    for(int i = 0; i <iis.size();i++){
        if(ii->imageFile == iis[i]->imageFile){
            return;
        }
    }
    iis.append(ii);
}

void DataModel::deleteImageInfo(ImageInfo* ii){
    iis.removeOne(ii);
    delete ii;
}

void DataModel::deleteImageInfo(QString imageFile){
    for(int i = 0; i <iis.size();i++){
        if(imageFile == iis[i]->imageFile){
            iis.removeOne(iis[i]);
            delete iis[i];
        }
    }
}

ImageInfo* DataModel::getImageInfo(QString imageFile){
    for(int i = 0; i <iis.size();i++){
        if(imageFile == iis[i]->imageFile){
            return iis[i];
        }
    }
}

void DataModel::clearTemp(){

}

void DataModel::emptyData(){
    iis.empty();
}
