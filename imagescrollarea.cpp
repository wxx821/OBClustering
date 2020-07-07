#include "imagescrollarea.h"

ImageScrollArea::ImageScrollArea(QWidget *parent) : QScrollArea(parent)
{

}

void ImageScrollArea::keyPressEvent(QKeyEvent *event){
    //QScrollArea::keyPressEvent(event);
    event->ignore();
}

void ImageScrollArea::keyReleaseEvent(QKeyEvent *event){
    //QScrollArea::keyReleaseEvent(event);
    event->ignore();
}
