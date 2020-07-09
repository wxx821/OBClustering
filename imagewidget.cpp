#include "imagewidget.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QVector>
#include <QSplitter>
#include <QCursor>
#include <QPolygon>
#include <QTimer>
#include <QEventLoop>
#include <QPolygonF>
#include "utils.h"
#include "mainwindow.h"
#include "waitingdialog.h"

const int ImageWidget::fromOObj=10;
const int ImageWidget::fromOObjBack=11;
const int ImageWidget::fromOFObj=12;
const int ImageWidget::fromOFObjBack=13;
const int ImageWidget::fromOBackObj=14;
const int ImageWidget::fromOBack=15;
const int ImageWidget::fromOFill1=16;
const int ImageWidget::fromOFillBack1=17;
const int ImageWidget::fromOFill2=18;
const int ImageWidget::fromOFillBack2=19;

const int ImageWidget::fromIObj=20;
const int ImageWidget::fromIObjBack=21;
const int ImageWidget::fromIFObj=22;
const int ImageWidget::fromIFObjBack=23;
const int ImageWidget::fromIBackObj=24;
const int ImageWidget::fromIBack=25;
const int ImageWidget::fromIFill1=26;
const int ImageWidget::fromIFillBack1=27;
const int ImageWidget::fromIFill2=28;
const int ImageWidget::fromIFillBack2=29;

const int ImageWidget::fromSObj=30;
const int ImageWidget::fromSObjBack=31;
const int ImageWidget::fromSFObj=32;
const int ImageWidget::fromSFObjBack=33;
const int ImageWidget::fromSBackObj=34;
const int ImageWidget::fromSBack=35;
const int ImageWidget::fromSFill1=36;
const int ImageWidget::fromSFillBack1=37;
const int ImageWidget::fromSFill2=38;
const int ImageWidget::fromSFillBack2=39;


ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    //this->index = index;
    myparent = parent;
    isFull = false;
    isFirstClicked = false;
    isDefiningEllipse = false;
    isDefiningRect = false;
    isDefiningRegion = false;
    isRegionDefined = false;
    isMoving = false;
    isRotating = false;
    isInner = false;
    angle = 0;
    this->region = nullptr;
//    this->ObjRegion = 0;
//    this->ObjBackRegion = 0;
//    this->FObjRegion = 0;
//    this->FObjBackRegion = 0;
//    this->BackObjRegion = 0;
//    this->BackRegion = 0;
//    this->FillRegion1 = 0;
//    this->FillBackRegion1 = 0;
//    this->FillRegion2 = 0;
//    this->FillBackRegion2 = 0;
    Define_Rect = new QAction(tr("矩形选择目标"), this);
    Define_Ellipse = new QAction(tr("椭圆选择目标"),this);
    Define_Poly = new QAction(tr("多边形选择目标"), this);
    Cancel_RDefining = new QAction(tr("取消选择"), this);
    Complete_RDefining = new QAction(tr("完成选择"), this);
    Import_Poly = new QAction(tr("导入选择方式"),this);
    Backfill1 = new QAction(tr("回填复原方法1"),this);
    Backfill2 = new QAction(tr("回填复原方法2"),this);
    Move = new QAction(tr("平移选择区域"), this);
    Rotate = new QAction(tr("旋转选择区域"),this);
    Zoom_In = new QAction(tr("放大选择区域"), this);
    Zoom_Out = new QAction(tr("缩小选择区域"),this);
    Apply = new QAction(tr("应用选择方式"),this);
    connect(Define_Rect, SIGNAL(triggered()), this, SLOT(defineRect()));
    connect(Define_Ellipse, SIGNAL(triggered()), this, SLOT(defineEllipse()));
    connect(Define_Poly, SIGNAL(triggered()), this, SLOT(definePoly()));
    connect(Cancel_RDefining, SIGNAL(triggered()), this, SLOT(cancelRDefining()));
    connect(Complete_RDefining, SIGNAL(triggered()), this, SLOT(completeRDefining()));
    connect(Import_Poly, SIGNAL(triggered()), this, SLOT(importPoly()));
    connect(Backfill1, SIGNAL(triggered()), this, SLOT(backfill1()));
    connect(Backfill2, SIGNAL(triggered()), this, SLOT(backfill2()));
    connect(Move, SIGNAL(triggered()), this, SLOT(move()));
    connect(Rotate, SIGNAL(triggered()), this, SLOT(rotate()));
    connect(Zoom_In, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(Zoom_Out, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(Apply, SIGNAL(triggered()), this, SLOT(apply()));

    l=new ImageLabel(this);
    qsa = new ImageScrollArea(this);
    qsa->setWidget(l);
    QGridLayout* lay = new QGridLayout(this);
    lay->addWidget(qsa,0,0);
    this->setLayout(lay);
    if(this->index == 0){
        this->voidmat = cv::imread("./image/void1.jpg");
        voidimage = Utils::MatToQImage(voidmat,voidimage);
    }
    else {
        this->voidmat = cv::imread("./image/void2.jpg");
        voidimage = Utils::MatToQImage(voidmat,voidimage);
    }
    this->draw();
}

ImageWidget::~ImageWidget(){
//    delete l;
//    delete qsa;
}

void ImageWidget::setData(DataModel *data){
    this->data = data;
}

void ImageWidget::setAnother(ImageWidget *another){
    this->another = another;
}

void ImageWidget::setResultWidget(ResultWidget *rw){
    this->rw = rw;
}

void ImageWidget::setMat(){
    this->from = 100;
    this->isRegionDefined = false;
    this->setMat(cv::Mat());
    this->region = nullptr;
    this->angle = 0;
    this->isDefiningRect = false;
    this->isDefiningRegion = false;
    this->isDefiningEllipse = false;
    this->draw();
}

void ImageWidget::setMat(cv::Mat m){
    this->mat = m;
    if(!this->mat.empty()){
        image = Utils::MatToQImage(mat,image);
        this->draw();
    }
}


void ImageWidget::draw(){
    if(!this->mat.empty()){
        QPixmap pixmap1 = QPixmap::fromImage(image);
        l->setScaledContents(false);
        l->resize(pixmap1.width(), pixmap1.height());

        QPainter painter(&pixmap1);
        QColor qc = QColor(Qt::red);
        QPen pen;
        pen.setColor(qc);
        pen.setWidth(4);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if(isDefiningRegion && isRegionDefined){
            painter.translate(region->centralPoint()->x,region->centralPoint()->y);
            painter.rotate(this->angle);
            painter.translate(-region->centralPoint()->x,-region->centralPoint()->y);
            QVector<cv::Point*> temppoints = region->poly;
            int size = temppoints.size();
            for(int i = 0; i < size - 1; i++){
                QPoint p1 = QPoint(temppoints[i]->x, temppoints[i]->y);
                QPoint p2 = QPoint(temppoints[i+1]->x, temppoints[i+1]->y);
                painter.drawLine(p1,p2);
            }
            QPoint p1 = QPoint(temppoints[size-1]->x, temppoints[size-1]->y);
            QPoint p2 = QPoint(temppoints[0]->x, temppoints[0]->y);
            painter.drawLine(p1,p2);
        }
        else if(isDefiningRegion){
            int size = points.size();
            for(int i = 0; i < size - 1; i++){
                QPoint p1 = QPoint(points[i]->x, points[i]->y);
                QPoint p2 = QPoint(points[i+1]->x, points[i+1]->y);
                painter.drawLine(p1,p2);
            }
            if(points.size()>0){
                QPoint p1 = QPoint(points[size-1]->x, points[size-1]->y);
                QPoint p2 = QPoint(ptemp.x, ptemp.y);
                painter.drawLine(p1,p2);
            }
        }
        else if(isDefiningRect && isRegionDefined){
            painter.translate(region->centralPoint()->x,region->centralPoint()->y);
            painter.rotate(this->angle);
            painter.translate(-region->centralPoint()->x,-region->centralPoint()->y);
            QVector<cv::Point*> temppoints = region->poly;
            int size = temppoints.size();
            for(int i = 0; i < size - 1; i++){
                QPoint p1 = QPoint(temppoints[i]->x, temppoints[i]->y);
                QPoint p2 = QPoint(temppoints[i+1]->x, temppoints[i+1]->y);
                painter.drawLine(p1,p2);
            }
            QPoint p1 = QPoint(temppoints[size-1]->x, temppoints[size-1]->y);
            QPoint p2 = QPoint(temppoints[0]->x, temppoints[0]->y);
            painter.drawLine(p1,p2);
        }
        else if(isDefiningEllipse && isRegionDefined){
            QVector<cv::Point*> temppoints = region->poly;
            QPoint p1 = QPoint(temppoints[0]->x, temppoints[0]->y);
            QPoint p3 = QPoint(temppoints[2]->x, temppoints[2]->y);
            //painter.resetTransform();
            painter.translate(region->centralPoint()->x,region->centralPoint()->y);
            painter.rotate(this->angle);
            painter.translate(-region->centralPoint()->x,-region->centralPoint()->y);
            painter.drawEllipse(p1.x(),p1.y(),abs(p3.x()-p1.x()),abs(p3.y()-p1.y()));
        }
        else if(isDefiningRect){
            painter.drawRect(rectRegion.x,rectRegion.y,rectRegion.width,rectRegion.height);
        }
        else if(isDefiningEllipse){
            painter.drawEllipse(rectRegion.x,rectRegion.y,rectRegion.width,rectRegion.height);
        }
        else{

        }
        l->setPixmap(pixmap1);
    }
    else {
        QPixmap pixmap1 = QPixmap::fromImage(voidimage);
        l->resize(pixmap1.width(), pixmap1.height());
        l->setScaledContents(true);
        l->setPixmap(pixmap1);
    }
}

void ImageWidget::contextMenuEvent(QContextMenuEvent *){
    if(!this->mat.empty()){
        QCursor cur=this->cursor();
        QMenu *menu;
        switch(from){
        case 11:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Define_Rect);
            menu->addAction(Define_Ellipse);
            menu->addAction(Define_Poly);
            menu->addAction(Import_Poly);
            menu->addSeparator();
            menu->addAction(Cancel_RDefining);
            menu->addAction(Complete_RDefining);
            menu->addSeparator();
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Backfill1);
            menu->addAction(Backfill2);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 13:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Backfill1);
            menu->addAction(Backfill2);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 15:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 21:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Define_Rect);
            menu->addAction(Define_Ellipse);
            menu->addAction(Define_Poly);
            menu->addAction(Import_Poly);
            menu->addSeparator();
            menu->addAction(Cancel_RDefining);
            menu->addAction(Complete_RDefining);
            menu->addSeparator();
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Backfill1);
            menu->addAction(Backfill2);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 23:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Backfill1);
            menu->addAction(Backfill2);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 25:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 31:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Define_Rect);
            menu->addAction(Define_Ellipse);
            menu->addAction(Define_Poly);
            menu->addAction(Import_Poly);
            menu->addSeparator();
            menu->addAction(Cancel_RDefining);
            menu->addAction(Complete_RDefining);
            menu->addSeparator();
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Backfill1);
            menu->addAction(Backfill2);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 33:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Backfill1);
            menu->addAction(Backfill2);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        case 35:
            menu=new QMenu(this);
            menu->setStyleSheet(QString::fromUtf8("border:0px"));
            menu->addAction(Move);
            menu->addAction(Rotate);
            menu->addAction(Zoom_In);
            menu->addAction(Zoom_Out);
            menu->addSeparator();
            menu->addAction(Apply);
            menu->exec(cur.pos()); //关联到光标
            break;
        default:
            break;
        }
    }
}

void ImageWidget::apply(){
    if(!this->mat.empty()&&this->isRegionDefined){
        WaitingDialog* wd = new WaitingDialog(this);
        wd->setLText("正在使得所定义的目标选择方式生效，需要若干秒的时间，请耐心等候......");
        wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
        wd->setFixedWidth(QApplication::desktop()->width()/2);
        wd->setFixedHeight(QApplication::desktop()->height()/10);
        wd->setModal(true);
        wd->show();
        wd->l->repaint();
        QEventLoop loop;//定义一个新的事件循环
        QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
        loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
        switch(this->from){
        case 11:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->oa->ObjBackRegion = region;
//            this->oa->objRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 13:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->oa->FObjBackRegion = region;
//            this->oa->fobjRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 15:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
            //this->oa->BackRegion = region;
            //this->oa->bobjRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 21:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->ia->ObjBackRegion = region;
//            this->ia->objRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 23:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->ia->FObjBackRegion = region;
//            this->ia->fobjRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 25:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->ia->BackRegion = region;
//            this->ia->bobjRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 31:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->sa->ObjBackRegion = region;
//            this->sa->objRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 33:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->sa->FObjBackRegion = region;
//            this->sa->fobjRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        case 35:
            this->another->setMat();
            this->region->rotate(this->image.width(),this->image.height());
//            this->sa->BackRegion = region;
//            this->sa->bobjRegionChanged();
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            break;
        default:
            break;
        }
        wd->close();
        this->draw();
        //delete wd;
    }
}

void ImageWidget::move(){
    if(this->isRegionDefined && !this->mat.empty()){
        isInner = false;
        this->isMoving = !this->isMoving;
        this->isRotating = false;
        this->Rotate->setText("旋转选择区域");
        if(this->isMoving){
            this->Move->setText("取消平移选择区域");
        }
        else{
            this->Move->setText("平移选择区域");
            this->setCursor(QCursor(Qt::ArrowCursor));
            this->isFirstClicked = false;
            region->setPoly(points);
            //region->poly = points;
            this->draw();
        }
    }
}

void ImageWidget::rotate(){
    if(this->isRegionDefined && !this->mat.empty()){
        isInner = false;
        this->isRotating = !this->isRotating;
        this->isMoving = false;
        this->Move->setText("平移选择区域");
        if(this->isRotating){
            this->Rotate->setText("取消旋转选择区域");
        }
        else{
            this->Rotate->setText("旋转选择区域");
            this->setCursor(QCursor(Qt::ArrowCursor));
            this->isFirstClicked = false;
            region->setPoly(points);
            //region->poly = points;
            this->draw();
        }
    }
}

void ImageWidget::zoomIn(){
    if(isRegionDefined && !this->mat.empty()){
        this->data->isChanged = true;
        this->region->zoom(1+SystemConfig::minRegionZoomFactor,this->image.width(),this->image.height());
        this->points = this->region->poly;

        this->draw();
    }
}

void ImageWidget::zoomOut(){
    if(isRegionDefined && !this->mat.empty()){
        this->data->isChanged = true;
        this->region->zoom(1/(1+SystemConfig::minRegionZoomFactor),this->image.width(),this->image.height());
        this->points = this->region->poly;
        this->draw();
    }
}

void ImageWidget::defineRect(){
    if(!this->mat.empty()){
        if(isRegionDefined){
            QMessageBox::StandardButton rb = QMessageBox::question(this, "目标选择", "目标已选择，是否再次选择目标？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb == QMessageBox::Yes){
                this->another->setMat();
                this->data->isChanged = true;
//                for(int i=0;i<points.size();i++){
//                    delete points[i];
//                }
                this->points.clear();
                this->rectRegion.x = 0;
                this->rectRegion.y = 0;
                this->rectRegion.width = 0;
                this->rectRegion.height = 0;
                isDefiningRect = true;
                isDefiningEllipse = false;
                isDefiningRegion = false;
                this->isFirstClicked = false;
                isRegionDefined = false;
//                switch(this->from){
//                case 11:
//                    this->oa->setRegionDefined(false);
//                    break;
//                case 21:
//                    this->ia->setRegionDefined(false);
//                    break;
//                case 31:
//                    this->sa->setRegionDefined(false);
//                    break;
//                default:
//                    break;
//                }
                this->isMoving = false;
                this->Move->setText("平移选择区域");
                this->isRotating = false;
                angle = 0;
                this->Rotate->setText("旋转选择区域");
                this->draw();
                if(this->index == 0){
                    this->rw->setMat1(this->mat, this->region);
                }
                else{
                    this->rw->setMat2(this->mat, this->region);
                }
            }
        }
        else{
            for(int i=0;i<points.size();i++){
                delete points[i];
            }
            this->points.clear();
            this->rectRegion.x = 0;
            this->rectRegion.y = 0;
            this->rectRegion.width = 0;
            this->rectRegion.height = 0;
            isDefiningRect = true;
            isDefiningEllipse = false;
            isDefiningRegion = false;
            this->isFirstClicked = false;
            this->isMoving = false;
            this->Move->setText("平移选择区域");
            this->isRotating = false;
            angle = 0;
            this->Rotate->setText("旋转选择区域");
            this->draw();
        }
    }
}

void ImageWidget::defineEllipse(){
    if(!this->mat.empty()){
        if(isRegionDefined){
            QMessageBox::StandardButton rb = QMessageBox::question(this, "目标选择", "目标已选择，是否再次选择目标？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb == QMessageBox::Yes){
                this->another->setMat();
                this->data->isChanged = true;
//                for(int i=0;i<points.size();i++){
//                    delete points[i];
//                }
                this->points.clear();
                this->rectRegion.x = 0;
                this->rectRegion.y = 0;
                this->rectRegion.width = 0;
                this->rectRegion.height = 0;
                isDefiningEllipse = true;
                isDefiningRect = false;
                isDefiningRegion = false;
                this->isFirstClicked = false;
                isRegionDefined = false;
//                switch(this->from){
//                case 11:
//                    this->oa->setRegionDefined(false);
//                    break;
//                case 21:
//                    this->ia->setRegionDefined(false);
//                    break;
//                case 31:
//                    this->sa->setRegionDefined(false);
//                    break;
//                default:
//                    break;
//                }
                this->isMoving = false;
                this->Move->setText("平移选择区域");
                this->isRotating = false;
                angle = 0;
                this->Rotate->setText("旋转选择区域");
                this->draw();
                if(this->index == 0){
                    this->rw->setMat1(this->mat, this->region);
                }
                else{
                    this->rw->setMat2(this->mat, this->region);
                }
            }
        }
        else{
            for(int i=0;i<points.size();i++){
                delete points[i];
            }
            this->points.clear();
            this->rectRegion.x = 0;
            this->rectRegion.y = 0;
            this->rectRegion.width = 0;
            this->rectRegion.height = 0;
            isDefiningEllipse = true;
            isDefiningRect = false;
            isDefiningRegion = false;
            this->isFirstClicked = false;
            this->isMoving = false;
            this->Move->setText("平移选择区域");
            this->isRotating = false;
            angle = 0;
            this->Rotate->setText("旋转选择区域");
            this->draw();
        }
    }
}

void ImageWidget::definePoly(){
    if(!this->mat.empty()){
        if(isRegionDefined){
            QMessageBox::StandardButton rb = QMessageBox::question(this, "目标选择", "目标已选择，是否再次选择目标？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb == QMessageBox::Yes){
                this->another->setMat();
                this->data->isChanged = true;
                isDefiningRegion = true;
                isDefiningEllipse = false;
                isDefiningRect = false;
//                for(int i=0;i<points.size();i++){
//                    delete points[i];
//                }
                this->points.clear();
                this->rectRegion.x = 0;
                this->rectRegion.y = 0;
                this->rectRegion.width = 0;
                this->rectRegion.height = 0;
                this->isFirstClicked = false;
                isRegionDefined = false;
//                switch(this->from){
//                case 11:
//                    this->oa->setRegionDefined(false);
//                    break;
//                case 21:
//                    this->ia->setRegionDefined(false);
//                    break;
//                case 31:
//                    this->sa->setRegionDefined(false);
//                    break;
//                default:
//                    break;
//                }
                this->isMoving = false;
                this->Move->setText("平移选择区域");
                this->isRotating = false;
                angle = 0;
                this->Rotate->setText("旋转选择区域");
                this->draw();
                if(this->index == 0){
                    this->rw->setMat1(this->mat, this->region);
                }
                else{
                    this->rw->setMat2(this->mat, this->region);
                }
            }
        }
        else{
            isDefiningRegion = true;
            isDefiningEllipse = false;
            isDefiningRect = false;
            for(int i=0;i<points.size();i++){
                delete points[i];
            }
            this->points.clear();
            this->rectRegion.x = 0;
            this->rectRegion.y = 0;
            this->rectRegion.width = 0;
            this->rectRegion.height = 0;
            this->isFirstClicked = false;
            this->isMoving = false;
            this->Move->setText("平移选择区域");
            this->isRotating = false;
            angle = 0;
            this->Rotate->setText("旋转选择区域");
            this->draw();
        }
    }
}

void ImageWidget::cancelRDefining(){
    if(!this->mat.empty()){
        if(isRegionDefined){
            QMessageBox::StandardButton rb = QMessageBox::question(this, "目标选择", "目标已选择，是否取消选择？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(rb == QMessageBox::Yes){
                this->another->setMat();
                this->data->isChanged = true;
//                for(int i=0;i<points.size();i++){
//                    delete points[i];
//                }
                this->points.clear();
                this->rectRegion.x = 0;
                this->rectRegion.y = 0;
                this->rectRegion.width = 0;
                this->rectRegion.height = 0;
                isDefiningRect = false;
                isDefiningEllipse = false;
                isDefiningRegion = false;
                this->isFirstClicked = false;
                isRegionDefined = false;
                this->isMoving = false;
                this->Move->setText("平移选择区域");
                this->isRotating = false;
                angle = 0;
                this->Rotate->setText("旋转选择区域");
                this->setMouseTracking(false);
                this->l->setMouseTracking(false);
                this->qsa->setMouseTracking(false);
//                switch(this->from){
//                case 11:
//                    this->oa->setRegionDefined(false);
//                    break;
//                case 21:
//                    this->ia->setRegionDefined(false);
//                    break;
//                case 31:
//                    this->sa->setRegionDefined(false);
//                    break;
//                default:
//                    break;
//                }
//                if(this->index == 0){
//                    this->rw->setMat1(this->mat, this->region);
//                }
//                else{
//                    this->rw->setMat2(this->mat, this->region);
//                }
            }
        }
        else{
            this->rectRegion.x = 0;
            this->rectRegion.y = 0;
            this->rectRegion.width = 0;
            this->rectRegion.height = 0;
//            for(int i=0;i<points.size();i++){
//                delete points[i];
//            }
            this->points.clear();
            this->isFirstClicked = false;
            isDefiningRegion =false;
            isDefiningEllipse = false;
            isDefiningRect = false;
            isRegionDefined = false;
            this->isMoving = false;
            this->Move->setText("平移选择区域");
            this->isRotating = false;
            angle = 0;
            this->Rotate->setText("旋转选择区域");
            this->setMouseTracking(false);
            this->l->setMouseTracking(false);
            this->qsa->setMouseTracking(false);
//            switch(this->from){
//            case 11:
//                this->oa->setRegionDefined(false);
//                break;
//            case 21:
//                this->ia->setRegionDefined(false);
//                break;
//            case 31:
//                this->sa->setRegionDefined(false);
//                break;
//            default:
//                break;
//            }
        }
        this->draw();
    }
}

void ImageWidget::backfill1(){
    if (!this->mat.empty() && this->isRegionDefined){
        this->data->isChanged = true;
//        switch(from){
//        case 11:
//            this->oa->objRegionFilled(0);
//            break;
//        case 13:
//            this->oa->fobjRegionFilled(0);
//            break;
//        case 21:
//            this->ia->objRegionFilled(0);
//            break;
//        case 23:
//            this->ia->fobjRegionFilled(0);
//            break;
//        case 31:
//            this->sa->objRegionFilled(0);
//            break;
//        case 33:
//            this->sa->fobjRegionFilled(0);
//            break;
//        default:
//            break;
//        }
    }
}

void ImageWidget::backfill2(){
    if (!this->mat.empty() && this->isRegionDefined){
        this->data->isChanged = true;
//        switch(from){
//        case 11:
//            this->oa->objRegionFilled(1);
//            break;
//        case 13:
//            this->oa->fobjRegionFilled(1);
//            break;
//        case 21:
//            this->ia->objRegionFilled(1);
//            break;
//        case 23:
//            this->ia->fobjRegionFilled(1);
//            break;
//        case 31:
//            this->sa->objRegionFilled(1);
//            break;
//        case 33:
//            this->sa->fobjRegionFilled(1);
//            break;
//        default:
//            break;
//        }
    }
}

void ImageWidget::importPoly(){
    this->cancelRDefining();
    //查询Region数据库，选定要导入的Region，构成一个Region
    Region* re = new Region();
//    RegionSelectionDialog* dialog = new RegionSelectionDialog(this,re);
//    dialog->exec();
//    if(re->isCanceled){
//        delete re;
//    }
//    else {
//        re->RegionName="";
//        RegionAddDialog* dialog2 = new RegionAddDialog(this,re);
//        dialog2->exec();
//        if(re->isCanceled){
//            delete re;
//        }
//        else {
//            this->another->setMat();
//            this->data->isChanged = true;
////            if(region!=nullptr){
////                delete region;
////            }

//            region = re;
//            WaitingDialog* wd = new WaitingDialog(this);
//            wd->setLText("正在使得所导入的目标选择方式生效，需要若干秒的时间，请耐心等候......");
//            wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
//            wd->setFixedWidth(QApplication::desktop()->width()/2);
//            wd->setFixedHeight(QApplication::desktop()->height()/10);
//            wd->setModal(true);
//            wd->show();
//            wd->l->repaint();
//            QEventLoop loop;//定义一个新的事件循环
//            QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//            loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
//            switch(this->from){
//            case 11:
//                this->oa->RegionID=region->DataID;
//                oa->ObjBackRegion = region;
//                this->oa->setRegionDefined(true);
//                break;
//            case 21:
//                this->ia->RegionID=region->DataID;
//                ia->ObjBackRegion = region;
//                this->ia->setRegionDefined(true);
//                break;
//            case 31:
//                this->sa->RegionID=region->DataID;
//                sa->ObjBackRegion = region;
//                this->sa->setRegionDefined(true);
//                break;
//            default:
//                break;
//            }
//            wd->close();
//            delete wd;
            this->isFirstClicked = false;
            isRegionDefined = true;
            this->angle = this->region->Angle;
            if(region->type == Region::TypePoly){
                this->isDefiningRegion = true;
                this->isDefiningRect = false;
                this->isDefiningEllipse = false;
            }
            else if(region->type == Region::TypeRect){
                this->isDefiningRect = true;
                this->isDefiningRegion = false;
                this->isDefiningEllipse = false;
            }
            else if(region->type == Region::TypeEllipse){
                this->isDefiningEllipse = true;
                this->isDefiningRect = false;
                this->isDefiningRegion = false;
            }
            else {
                this->isDefiningRect = false;
                this->isDefiningRegion = false;
                this->isDefiningEllipse = false;
            }
            if(this->index == 0){
                this->rw->setMat1(this->mat, this->region);
            }
            else{
                this->rw->setMat2(this->mat, this->region);
            }
            this->setMouseTracking(false);
            this->l->setMouseTracking(false);
            this->qsa->setMouseTracking(false);
            this->draw();
//        }
        //delete dialog;
        //delete dialog2;
//    }
}

void ImageWidget::completeRDefining(){
    if(!this->mat.empty()){
        if((isDefiningRect) && this->rectRegion.width == 0&&isFirstClicked&&!isRegionDefined){
            QMessageBox::information(this,tr("目标选择"),tr("矩形选择方式定义尚未完成，需要定义两个顶点。"));
        }
        else if((isDefiningEllipse) && this->rectRegion.width == 0&&isFirstClicked&&!isRegionDefined){
            QMessageBox::information(this,tr("目标选择"),tr("椭圆选择方式定义尚未完成，需要定义两个顶点。"));
        }
        else if(isDefiningRect && !(this->rectRegion.width == 0)&& !isRegionDefined){
            this->another->setMat();
//            if(region!=nullptr){
//                delete region;
//            }
            cv::Point* p1 = new cv::Point(rectRegion.x, rectRegion.y);
            cv::Point* p2 = new cv::Point(rectRegion.x+rectRegion.width,rectRegion.y);
            cv::Point* p3 = new cv::Point(rectRegion.x+rectRegion.width,rectRegion.y+rectRegion.height);
            cv::Point* p4 = new cv::Point(rectRegion.x,rectRegion.y+rectRegion.height);
            //QVector<Point> points1;
            points.clear();
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p4);
            //生成真目标背景选择区域

            region = new Region(Region::TypeRect, cv::Scalar(255,0,0), points);
            region->setPoly(points);
//            RegionAddDialog* dialog = new RegionAddDialog(this,region);
//            dialog->setModal(true);
//            dialog->exec();
//            if(region->isCanceled){
//                this->cancelRDefining();
//            }
//            else {
//                this->data->isChanged = true;
//                WaitingDialog* wd = new WaitingDialog(this);
//                wd->setLText("正在生成目标选择方式及相关图像，需要若干秒的时间，请耐心等候......");
//                wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
//                wd->setFixedWidth(QApplication::desktop()->width()/2);
//                wd->setFixedHeight(QApplication::desktop()->height()/10);
//                wd->setModal(true);
//                wd->show();
//                wd->l->repaint();
//                wd->repaint();
//                QEventLoop loop;//定义一个新的事件循环
//                QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//                loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
//                switch(this->from){
//                case 11:
//                    this->oa->RegionID=region->DataID;
//                    this->oa->ObjBackRegion = region;
//                    this->oa->setRegionDefined(true);
//                    break;
//                case 21:
//                    this->ia->RegionID=region->DataID;
//                    this->ia->ObjBackRegion = region;
//                    this->ia->setRegionDefined(true);
//                    break;
//                case 31:
//                    this->sa->RegionID=region->DataID;
//                    this->sa->ObjBackRegion = region;
//                    this->sa->setRegionDefined(true);
//                    break;
//                default:
//                    break;
//                }
//                this->isFirstClicked = false;
//                isRegionDefined = true;
//                if(this->index == 0){
//                    this->rw->setMat1(this->mat, this->region);
//                }
//                else{
//                    this->rw->setMat2(this->mat, this->region);
//                }
//                this->setMouseTracking(false);
//                this->l->setMouseTracking(false);
//                this->qsa->setMouseTracking(false);
//                wd->close();
//                delete wd;
//            }
        }
        else if(isDefiningEllipse && !(this->rectRegion.width == 0)&& !isRegionDefined){
            this->another->setMat();
//            if(region != nullptr){
//                delete region;
//            }
            cv::Point* p1 = new cv::Point(rectRegion.x, rectRegion.y);
            cv::Point* p2 = new cv::Point(rectRegion.x+rectRegion.width,rectRegion.y);
            cv::Point* p3 = new cv::Point(rectRegion.x+rectRegion.width,rectRegion.y+rectRegion.height);
            cv::Point* p4 = new cv::Point(rectRegion.x,rectRegion.y+rectRegion.height);
            //QVector<Point> points1;
            points.clear();
            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);
            points.push_back(p4);

            region = new Region(Region::TypeEllipse, cv::Scalar(255,0,0), points);
            region->setPoly(points);
//            RegionAddDialog* dialog = new RegionAddDialog(this,region);
//            dialog->exec();
//            if(region->isCanceled){
//                this->cancelRDefining();
//            }
//            else {
//                WaitingDialog* wd = new WaitingDialog(this);
//                wd->setLText("正在生成目标选择方式及相关图像，需要若干秒的时间，请耐心等候......");
//                wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
//                wd->setFixedWidth(QApplication::desktop()->width()/2);
//                wd->setFixedHeight(QApplication::desktop()->height()/10);
//                wd->setModal(true);
//                wd->show();
//                wd->l->repaint();
//                QEventLoop loop;//定义一个新的事件循环
//                QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//                loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
//                this->data->isChanged = true;
//                switch(this->from){
//                case 11:
//                    this->oa->RegionID=region->DataID;
//                    this->oa->ObjBackRegion = region;
//                    this->oa->setRegionDefined(true);
//                    break;
//                case 21:
//                    this->ia->RegionID=region->DataID;
//                    this->ia->ObjBackRegion = region;
//                    this->ia->setRegionDefined(true);
//                    break;
//                case 31:
//                    this->sa->RegionID=region->DataID;
//                    this->sa->ObjBackRegion = region;
//                    this->sa->setRegionDefined(true);
//                    break;
//                default:
//                    break;
//                }
                this->isFirstClicked = false;
                isRegionDefined = true;
                if(this->index == 0){
                    this->rw->setMat1(this->mat, this->region);
                }
                else{
                    this->rw->setMat2(this->mat, this->region);
                }
                this->setMouseTracking(false);
                this->l->setMouseTracking(false);
                this->qsa->setMouseTracking(false);
                //delete wd;
            }
            //delete dialog;
        }
        else if(isDefiningRegion && (this->points.size() <= 2)&&!isRegionDefined){
            QMessageBox::information(this,tr("监控区域定义"),tr("多边形监控区域的定义尚未完成，至少需要定义三个顶点"));
            this->isFirstClicked = false;
        }
        else if(isDefiningRegion && (this->points.size() > 2)&&!isRegionDefined){
   //         QVector<Point*> points1;
   //         for(int i = 0; i < points.size(); i++){
   //             Point* pp2 = new Point(points[i]->x, points[i]->y);
   //             points1.push_back(pp2);
   //         }
            this->another->setMat();
//            if(region != nullptr){
//                delete region;
//            }
            region = new Region(Region::TypePoly, cv::Scalar(255,0,0), points);
            region->setPoly(points);
//            RegionAddDialog* dialog = new RegionAddDialog(this,region);
//            dialog->exec();
//            if(region->isCanceled){
//                this->cancelRDefining();
//            }
//            else {
//                WaitingDialog* wd = new WaitingDialog(this);
//                wd->setLText("正在生成目标选择方式及相关图像，需要若干秒的时间，请耐心等候......");
//                wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
//                wd->setFixedWidth(QApplication::desktop()->width()/2);
//                wd->setFixedHeight(QApplication::desktop()->height()/10);
//                wd->setModal(true);
//                wd->show();
//                wd->l->repaint();
//                QEventLoop loop;//定义一个新的事件循环
//                QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//                loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
//                this->data->isChanged = true;
//                switch(this->from){
//                case 11:
//                    this->oa->RegionID=region->DataID;
//                    this->oa->ObjBackRegion = region;
//                    this->oa->setRegionDefined(true);
//                    break;
//                case 21:
//                    this->ia->RegionID=region->DataID;
//                    this->ia->ObjBackRegion = region;
//                    this->ia->setRegionDefined(true);
//                    break;
//                case 31:
//                    this->sa->RegionID=region->DataID;
//                    this->sa->ObjBackRegion = region;
//                    this->sa->setRegionDefined(true);
//                    break;
//                default:
//                    break;
//                }
//                this->isFirstClicked = false;
//                isRegionDefined = true;
//                if(this->index == 0){
//                    this->rw->setMat1(this->mat, this->region);
//                }
//                else{
//                    this->rw->setMat2(this->mat, this->region);
//                }
//                this->setMouseTracking(false);
//                this->l->setMouseTracking(false);
//                this->qsa->setMouseTracking(false);
//                wd->close();
//                delete wd;
//            }
            //delete dialog;
        }
        else{

        }
        this->draw();
//    }
}

void ImageWidget::mouseDoubleClickEvent(QMouseEvent *e){
    isFull = !isFull;
    if(isFull){
        mysize = this->size();
        myflags = this->windowFlags();
        this->setParent(0);
        this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
        this->showFullScreen();
        this->resize(QApplication::desktop()->size());
    }
    else{
        //myparent->setLayout(myparentlayout);
        this->resize(mysize);
        this->setParent(myparent);
        QSplitter* qsp = ((MainWindow*)this->parentWidget())->splitter1;
        if(this->index == 0){
            qsp->insertWidget(0,this);
        }
        else{
            qsp->addWidget(this);
        }
        this->overrideWindowFlags(myflags);
        this->showNormal();
    }
}

void ImageWidget::mousePressEvent(QMouseEvent *e){
    cv::Rect nrect;
    if(e->button() == Qt::LeftButton && (isDefiningRect||isDefiningEllipse) && !isFirstClicked &&!isRegionDefined && !this->mat.empty()){
       isFirstClicked = true;
       QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
       double x_offset = scrollBar_X->value();
       QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
       double y_offset = scrollBar_Y->value();
       position11 = QPoint(e->pos().x()+x_offset, e->pos().y()+y_offset);
       this->l->setMouseTracking(true);
       this->setMouseTracking(true);
       this->qsa->setMouseTracking(true);
    }
    else if(e->button() == Qt::LeftButton && (isDefiningRect||isDefiningEllipse) && isFirstClicked && !isRegionDefined && !this->mat.empty()){
        isFirstClicked = false;
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        int posX = e->x()+x_offset;
        int posY = e->y()+y_offset;
        int x_position22;
        int y_position22;
        if(posX>this->width())
        {
            x_position22 = e->x()+x_offset;
        }
        else if( posX< 0)
        {
            x_position22 =0;
        }
        else
        {
            x_position22 = e->x()+x_offset;
        }
        if( posY>this->height())
        {
            y_position22 = e->y()+y_offset;
        }

        else if ( posY < 0)
        {
            y_position22=0;
        }
        else
        {
            y_position22=posY;
        }
        if(x_position22<=this->width()+x_offset && y_position22<=this->height()+y_offset){
            if(position11.x()<x_position22 && position11.y()<y_position22)
            {
                nrect.x=position11.x();
                nrect.y=position11.y();
                nrect.width=x_position22-position11.x();
                nrect.height=y_position22-position11.y();
            }
            else if(position11.x()<x_position22 && position11.y()> y_position22)
            {
                nrect.x=position11.x();
                nrect.y=y_position22;
                nrect.width=x_position22-position11.x();
                nrect.height=position11.y()-y_position22;
            }
            else if(position11.x()>x_position22 && position11.y()< y_position22)
            {
                nrect.x=x_position22;
                nrect.y=position11.y();
                nrect.width=position11.x()-x_position22;
                nrect.height=y_position22-position11.y();
            }
            else if(position11.x()>x_position22 && position11.y()> y_position22)
            {
                nrect.x=x_position22;
                nrect.y=y_position22;
                nrect.width=position11.x()-x_position22;
                nrect.height=position11.y()-y_position22;
            }
        }
        if(nrect.width<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else if(nrect.height<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else{
            this->rectRegion.x = nrect.x;
            this->rectRegion.y = nrect.y;
            this->rectRegion.width = nrect.width;
            this->rectRegion.height = nrect.height;

        }
        this->completeRDefining();
        //this->draw();
    }
    else if(e->button() == Qt::LeftButton && isDefiningRegion &&!isRegionDefined && !this->mat.empty()){
        QPoint qp = e->pos();
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        cv::Point* p = new cv::Point(qp.x()+x_offset,qp.y()+y_offset);
        ptemp = cv::Point(qp.x()+x_offset,qp.y()+y_offset);
        this->points.push_back(p);
        this->l->setMouseTracking(true);
        this->setMouseTracking(true);
        this->qsa->setMouseTracking(true);
        this->draw();
    }
    else if(e->button() == Qt::LeftButton && (isMoving) && isRegionDefined && !this->mat.empty()){
       QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
       double x_offset = scrollBar_X->value();
       QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
       double y_offset = scrollBar_Y->value();
       position11 = QPoint(e->pos().x()+x_offset, e->pos().y()+y_offset);
       isInner = region->isInner(cv::Point(e->pos().x()+x_offset, e->pos().y()+y_offset));
       if(isInner){
           this->setCursor(QCursor(Qt::SizeAllCursor));
           this->l->setMouseTracking(true);
           this->setMouseTracking(true);
           this->qsa->setMouseTracking(true);
       }
    }
    else if(e->button() == Qt::LeftButton && (isRotating) && isRegionDefined && !this->mat.empty()){
       QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
       double x_offset = scrollBar_X->value();
       QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
       double y_offset = scrollBar_Y->value();
       position11 = QPoint(e->pos().x()+x_offset, e->pos().y()+y_offset);
       isInner = region->isInner(cv::Point(e->pos().x()+x_offset, e->pos().y()+y_offset));
       if(isInner){
           this->setCursor(QCursor(QPixmap("./image/rotate.png")));
           this->l->setMouseTracking(true);
           this->setMouseTracking(true);
           this->qsa->setMouseTracking(true);
       }
    }
    else{

    }

    e->ignore();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *e){
    //qDebug()<<e->pos().x()<<";"<<e->pos().y();
    cv::Rect nrect;
    if((isDefiningRect||isDefiningEllipse) && isFirstClicked && !isRegionDefined && !this->mat.empty()){
        //isFirstClicked = false;
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        int posX = e->x()+x_offset;
        int posY = e->y()+y_offset;
        int x_position22;
        int y_position22;
        if(posX>this->width())
        {
            x_position22 = e->x()+x_offset;
        }
        else if( posX< 0)
        {
            x_position22 =0;
        }
        else
        {
            x_position22 = e->x()+x_offset;
        }
        if( posY>this->height())
        {
            y_position22 = e->y()+y_offset;
        }

        else if ( posY < 0)
        {
            y_position22=0;
        }
        else
        {
            y_position22=posY;
        }
        if(x_position22<=this->width()+x_offset && y_position22<=this->height()+y_offset){
            if(position11.x()<x_position22 && position11.y()<y_position22)
            {
                nrect.x=position11.x();
                nrect.y=position11.y();
                nrect.width=x_position22-position11.x();
                nrect.height=y_position22-position11.y();
            }
            else if(position11.x()<x_position22 && position11.y()> y_position22)
            {
                nrect.x=position11.x();
                nrect.y=y_position22;
                nrect.width=x_position22-position11.x();
                nrect.height=position11.y()-y_position22;
            }
            else if(position11.x()>x_position22 && position11.y()< y_position22)
            {
                nrect.x=x_position22;
                nrect.y=position11.y();
                nrect.width=position11.x()-x_position22;
                nrect.height=y_position22-position11.y();
            }
            else if(position11.x()>x_position22 && position11.y()> y_position22)
            {
                nrect.x=x_position22;
                nrect.y=y_position22;
                nrect.width=position11.x()-x_position22;
                nrect.height=position11.y()-y_position22;
            }
        }
        if(nrect.width<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else if(nrect.height<0){
            this->rectRegion.width = -nrect.width;
            this->rectRegion.height= -nrect.height;
            this->rectRegion.x = nrect.x+nrect.width;
            this->rectRegion.y = nrect.y+nrect.height;
        }
        else{
            this->rectRegion.x = nrect.x;
            this->rectRegion.y = nrect.y;
            this->rectRegion.width = nrect.width;
            this->rectRegion.height = nrect.height;

        }
        this->draw();
    }
    else if(isDefiningRegion &&!isRegionDefined && !this->mat.empty()){
        QPoint qp = e->pos();
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        ptemp = cv::Point(qp.x()+x_offset,qp.y()+y_offset);
        //this->points.push_back(p);
        this->draw();
    }
    else if(isMoving && isInner && isRegionDefined && this->mat.empty()){
        this->data->isChanged = true;
        //isFirstClicked = false;
        QPoint qp = e->pos();
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        double posX = qp.x()+x_offset;
        double posY = qp.y()+y_offset;
        this->region->move(posX-position11.x(),posY-position11.y(),this->image.width(),this->image.height());
        //qDebug()<<posX-position11.x()<<posY-position11.y()<<this->image.width()<<this->image.height();
        //this->points = region->poly;
        this->draw();
    }
    else if(isRotating && isInner && isRegionDefined && !this->mat.empty()){
        this->data->isChanged = true;
        QPoint qp = e->pos();
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        double posX = qp.x()+x_offset;
        double posY = qp.y()+y_offset;
        double angle = this->region->getAngle(new cv::Point(position11.x(),position11.y()),new cv::Point(posX,posY));
        this->angle+=angle;
        this->region->setRotateAngle(this->angle);
        //this->region->rotate(new Point(position11.x(),position11.y()),new Point(posX,posY),this->image.width(),this->image.height());
        //this->points = region->poly;
        this->draw();
    }
    else{

    }
    e->ignore();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *e){
    cv::Rect nrect;
    if(e->button() == Qt::LeftButton && isMoving && isInner && isRegionDefined && !this->mat.empty()){
        this->data->isChanged = true;
        QPoint qp = e->pos();
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        double posX = qp.x()+x_offset;
        double posY = qp.y()+y_offset;
        this->region->move(posX-position11.x(),posY-position11.y(),this->image.width(),this->image.height());
        //qDebug()<<posX-position11.x()<<posY-position11.y()<<this->image.width()<<this->image.height();
        this->points = region->poly;
        isInner = false;
        this->setCursor(QCursor(Qt::ArrowCursor));
        this->setMouseTracking(false);
        this->l->setMouseTracking(false);
        this->qsa->setMouseTracking(false);
        //this->move();
        this->draw();
    }
    else if(e->button() == Qt::LeftButton && isRotating && isInner && isRegionDefined && !this->mat.empty()){
        this->data->isChanged = true;
        QPoint qp = e->pos();
        QScrollBar *scrollBar_X = qsa->horizontalScrollBar();
        double x_offset = scrollBar_X->value();
        QScrollBar *scrollBar_Y = qsa->verticalScrollBar();
        double y_offset = scrollBar_Y->value();
        double posX = qp.x()+x_offset;
        double posY = qp.y()+y_offset;
//        this->region->rotate(new Point(position11.x(),position11.y()),new Point(posX,posY),this->image.width(),this->image.height());
//        //qDebug()<<posX-position11.x()<<posY-position11.y()<<this->image.width()<<this->image.height();
//        this->points = region->poly;
        double angle = this->region->getAngle(new cv::Point(position11.x(),position11.y()),new cv::Point(posX,posY));
        this->angle+=angle;
        this->region->setRotateAngle(this->angle);
        isInner = false;
        this->setCursor(QCursor(Qt::ArrowCursor));
        this->setMouseTracking(false);
        this->l->setMouseTracking(false);
        this->qsa->setMouseTracking(false);
        //this->rotate();
        this->draw();
    }

    e->ignore();
}

void ImageWidget::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Up){
        if(isMoving && isRegionDefined && !this->mat.empty()){
            this->data->isChanged = true;
            this->region->move(0,-SystemConfig::minMoveFactor,this->image.width(),this->image.height());
            this->draw();
        }
        else if(isRotating && isRegionDefined){
//            this->region->rotate(-SystemConfig::minRotateFactor,this->image.width(),this->image.height());
//            this->points = region->poly;
            this->data->isChanged = true;
            this->angle-=SystemConfig::minRotateFactor;
            this->region->setRotateAngle(this->angle);
            this->draw();
        }
        else if(isRegionDefined && !this->mat.empty()){
//            this->region->zoom(1/(1+SystemConfig::minRegionZoomFactor),this->image.width(),this->image.height());
//            this->draw();
            this->zoomOut();
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(isMoving && isRegionDefined && !this->mat.empty()){
            this->data->isChanged = true;
            this->region->move(0,SystemConfig::minMoveFactor,this->image.width(),this->image.height());
            this->draw();
        }
        else if(isRotating && isRegionDefined && !this->mat.empty()){
//            this->region->rotate(SystemConfig::minRotateFactor,this->image.width(),this->image.height());
//            this->points = region->poly;
            this->data->isChanged = true;
            this->angle+=SystemConfig::minRotateFactor;
            this->region->setRotateAngle(this->angle);
            this->draw();
        }
        else if(isRegionDefined && !this->mat.empty()){
//            this->region->zoom((1+SystemConfig::minRegionZoomFactor),this->image.width(),this->image.height());
//            this->draw();
            this->zoomIn();
        }
    }
    else if(event->key() == Qt::Key_Left){
        if(isMoving && isRegionDefined && !this->mat.empty()){
            this->data->isChanged = true;
            this->region->move(-SystemConfig::minMoveFactor,0,this->image.width(),this->image.height());
            this->draw();
        }
        else if(isRotating && isRegionDefined && !this->mat.empty()){
//            this->region->rotate(-SystemConfig::minRotateFactor,this->image.width(),this->image.height());
//            this->points = region->poly;
            this->data->isChanged = true;
            this->angle-=SystemConfig::minRotateFactor;
            this->region->setRotateAngle(this->angle);
            this->draw();
        }
        else if(isRegionDefined && !this->mat.empty()){
//            this->region->zoom(1/(1+SystemConfig::minRegionZoomFactor),this->image.width(),this->image.height());
//            this->draw();
            this->zoomOut();
        }
    }
    else if(event->key() == Qt::Key_Right){
        if(isMoving && isRegionDefined && !this->mat.empty()){
            this->data->isChanged = true;
            this->region->move(SystemConfig::minMoveFactor,0,this->image.width(),this->image.height());
            this->draw();
        }
        else if(isRotating && isRegionDefined && !this->mat.empty()){
//            this->region->rotate(SystemConfig::minRotateFactor,this->image.width(),this->image.height());
//            this->points = region->poly;
            this->data->isChanged = true;
            this->angle+=SystemConfig::minRotateFactor;
            this->region->setRotateAngle(this->angle);
            this->draw();
        }
        else if(isRegionDefined && !this->mat.empty()){
//            this->region->zoom((1+SystemConfig::minRegionZoomFactor),this->image.width(),this->image.height());
//            this->draw();
            this->zoomIn();
        }
    }
    else if(event->key() == Qt::Key_Escape){
        this->cancelRDefining();
    }
}

void ImageWidget::keyReleaseEvent(QKeyEvent *event){

}
