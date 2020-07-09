#include "simagewidget.h"
#include <QGridLayout>
#include <QImage>
#include "utils.h"

SImageWidget::SImageWidget(QWidget *parent) : QWidget(parent)
{
    l=new ImageLabel(this);
    qsa = new ImageScrollArea(this);
    qsa->setWidget(l);
    QGridLayout* lay = new QGridLayout(this);
    lay->addWidget(qsa,0,0);
    this->setLayout(lay);
}

void SImageWidget::setSImageFile(QString sfile){
    this->sfile = sfile;
    cv::Mat mat = cv::imread(sfile.toStdString());
    QImage image;
    image = Utils::MatToQImage(mat,image);
    QPixmap pixmap1 = QPixmap::fromImage(image);
    l->setScaledContents(false);
    l->resize(pixmap1.width(), pixmap1.height());
    l->setPixmap(pixmap1);
}
