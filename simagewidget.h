#ifndef SIMAGEWIDGET_H
#define SIMAGEWIDGET_H

#include <QWidget>
#include <QString>
//opencv的头文件
#include <QVector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "imagelabel.h"
#include "imagescrollarea.h"


class SImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SImageWidget(QWidget *parent = nullptr);

    void setSImageFile(QString sfile);

signals:

public slots:

private:
    QString sfile;
    ImageLabel* l;
    ImageScrollArea* qsa;
};

#endif // SIMAGEWIDGET_H
