#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QScrollArea>
#include <QMainWindow>
#include <QRect>
#include <QImage>
#include <QSize>
#include <QLayout>
//opencv的头文件
#include <QVector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "region.h"
#include "imagelabel.h"
#include "imagescrollarea.h"
#include "systemconfig.h"
#include "datamodel.h"
#include "resultwidget.h"

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();
    static const int fromOObj;
    static const int fromOObjBack;
    static const int fromOFObj;
    static const int fromOFObjBack;
    static const int fromOBackObj;
    static const int fromOBack;
    static const int fromOFill1;
    static const int fromOFillBack1;
    static const int fromOFill2;
    static const int fromOFillBack2;

    static const int fromIObj;
    static const int fromIObjBack;
    static const int fromIFObj;
    static const int fromIFObjBack;
    static const int fromIBackObj;
    static const int fromIBack;
    static const int fromIFill1;
    static const int fromIFillBack1;
    static const int fromIFill2;
    static const int fromIFillBack2;

    static const int fromSObj;
    static const int fromSObjBack;
    static const int fromSFObj;
    static const int fromSFObjBack;
    static const int fromSBackObj;
    static const int fromSBack;
    static const int fromSFill1;
    static const int fromSFillBack1;
    static const int fromSFill2;
    static const int fromSFillBack2;

    QAction* Define_Rect;
    QAction* Define_Ellipse;
    QAction* Define_Poly;
    QAction* Cancel_RDefining;
    QAction* Complete_RDefining;
    QAction* Move;
    QAction* Rotate;
    QAction* Zoom_In;
    QAction* Zoom_Out;
    QAction* Import_Poly;
    QAction* Backfill1;
    QAction* Backfill2;
    QAction* Apply;

    int index;
    int from;
    cv::Rect rectRegion;
    QVector<cv::Point*> points;

    bool isFirstClicked;
    bool isDefiningRegion;
    bool isDefiningEllipse;
    bool isDefiningRect;
    bool isRegionDefined;
    bool isFull;
    bool isMoving;
    bool isRotating;
    bool isInner;
    QPoint position11;
    QPoint position22;
    cv::Point ptemp;
    double angle;

    void setData(DataModel* data);
    void setResultWidget(ResultWidget* rw);

    void setMat(cv::Mat m);
    void setMat();
    void setAnother(ImageWidget* another);
    void contextMenuEvent(QContextMenuEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *event);//键盘按下事件
    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件

public slots:
    void defineRect();
    void defineEllipse();
    void definePoly();
    void cancelRDefining();
    void completeRDefining();
    void backfill1();
    void backfill2();
    void importPoly();
    void move();
    void rotate();
    void zoomIn();
    void zoomOut();
    void apply();
signals:

private:
    DataModel* data;
    ResultWidget* rw;

    cv::Mat mat;
    cv::Mat voidmat;

    Region* region;

    ImageWidget* another;

    ImageLabel* l;
    ImageScrollArea* qsa;
    QImage image;
    QImage voidimage;
    QWidget* myparent;
    QSize mysize;
    Qt::WindowFlags myflags;
    void draw();

};

#endif // IMAGEWIDGET_H
