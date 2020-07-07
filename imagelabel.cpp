#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent)
{

}

void ImageLabel::mousePressEvent(QMouseEvent *e){
    e->ignore();
}

void ImageLabel::contextMenuEvent(QContextMenuEvent *e){
    e->ignore();
}

void ImageLabel::mouseDoubleClickEvent(QMouseEvent *e){
    e->ignore();
}

void ImageLabel::mouseMoveEvent(QMouseEvent *e){
    e->ignore();
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *e){
    e->ignore();
}
