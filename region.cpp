//OpenCV头文件
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QUuid>
#include <QString>
#include <qmath.h>
#include <QDateTime>
#include <QStringList>
#include <QDebug>
#include "region.h"
#include "systemconfig.h"
#include "utils.h"

using namespace std;

const int Region::TypeRect=0;
const int Region::TypeEllipse=1;
const int Region::TypePoly=2;

const QString Region::Table_Name="Region";
const QString Region::Table_CName=QString::fromUtf8("选择方式数据表");

const QString Region::DataID_Name="DataID";
const QString Region::RegionName_Name="RegionName";
const QString Region::ObjID_Name="ObjID";
const QString Region::ObjType_Name="ObjType";
const QString Region::VNum_Name="VNum";
const QString Region::X_Name="X";
const QString Region::Y_Name="Y";
const QString Region::Angle_Name="Angle";
const QString Region::Time_Name="TTime";
const QString Region::Intro_Name="Intro";

const QString Region::DataID_CName=QString::fromUtf8("选择方式ID");
const QString Region::RegionName_CName=QString::fromUtf8("选择方式名称");
const QString Region::ObjID_CName=QString::fromUtf8("目标ID");
const QString Region::ObjType_CName=QString::fromUtf8("目标类型");
const QString Region::VNum_CName=QString::fromUtf8("顶点序号");
const QString Region::X_CName=QString::fromUtf8("顶点X坐标");
const QString Region::Y_CName=QString::fromUtf8("顶点Y坐标");
const QString Region::Angle_CName=QString::fromUtf8("旋转角度");
const QString Region::Time_CName=QString::fromUtf8("定义时间");
const QString Region::Intro_CName=QString::fromUtf8("备注");

Region::Region(){
    this->isSelected = false;
    DataID=Region::generateID();
    RegionName="";
    ObjID="";
    ObjType=0;
    VNum=0;
    X="";
    Y="";
    Angle=0;
    Time=QDateTime::currentDateTime();
    Intro="目标选择区域创建于"+Time.toString();
    this->color = cv::Scalar(255,0,0);
    isCanceled = false;
}

Region::Region(int type, cv::Scalar c){
    this->isSelected = false;
    DataID=Region::generateID();
    RegionName="";
    ObjID="";
    ObjType=type;
    VNum=0;
    X="";
    Y="";
    Angle=0;
    Time=QDateTime::currentDateTime();
    Intro="目标选择区域创建于"+Time.toString();
    this->color = c;
    this->type = type;
    isCanceled = false;
}

Region::Region(int type, cv::Scalar c, QVector<cv::Point*> ps){
    this->isSelected = false;
    DataID=Region::generateID();
    RegionName="";
    ObjID="";
    ObjType=type;
    VNum=0;
    X="";
    Y="";
    Angle=0;
    Time=QDateTime::currentDateTime();
    Intro="目标选择区域创建于"+Time.toString();
    this->color = c;
    this->type = type;
    this->poly = ps;
    isCanceled = false;
}

Region::~Region(){
    delete cp;
    for(int i = 0;i< this->poly.size();i++){
        cv::Point* p = this->poly[i];
        delete p;
    }
    this->poly.clear();
}

void Region::draw(cv::Mat mat){
    QVector<cv::Point> poly = this->getPolyAfterRotating();
    if(this->type == Region::TypeEllipse){
        //画旋转的椭圆
        cv::ellipse(mat,cv::Point(this->poly[0]->x+(this->poly[2]->x-this->poly[0]->x)/2,this->poly[0]->y+
                (this->poly[2]->y-this->poly[0]->y)/2),cv::Size((this->poly[2]->x-this->poly[0]->x)/2,(this->poly[2]->y
                -this->poly[0]->y)/2),this->Angle,0,360,cv::Scalar(0,0,255),2);
    }
    else{
//        int size = poly.size();
//        cv::Point points[1][size];
//        cv::Point points2[1][size];
//        for(int i = 0; i < size; i++){
//            points[0][i] = cv::Point(poly[i].x,poly[i].y);
//            cv::Point p2 = cv::Point(poly[i].x+mat.cols/2,poly[i].y);
//            points2[0][i] = p2;
//        }

//        const cv::Point* ppt[1] = {points[0]};
//        int npt[] = {size};
//        const cv::Point* ppt2[1] = {points2[0]};
//        int npt2[] = {size};
//        cv::polylines(mat, ppt, npt, 1, true, this->color, 2);
//        cv::polylines(mat, ppt2, npt2, 1, true, this->color, 2);

        int size = poly.size();
        for(int i = 0; i < size - 1; i++){
            cv::Point p1 = cv::Point(poly[i].x, poly[i].y);
            cv::Point p2 = cv::Point(poly[i+1].x, poly[i+1].y);
            cv::line(mat,p1,p2,cv::Scalar(0,0,255),2);
        }
        cv::Point p1 = cv::Point(poly[size-1].x, poly[size-1].y);
        cv::Point p2 = cv::Point(poly[0].x, poly[0].y);
        cv::line(mat,p1,p2,cv::Scalar(0,0,255),2);
    }
}

cv::Mat Region::draw(){
    QVector<cv::Point> poly = this->getPolyAfterRotating();
    cv::Point left = leftPointAfterRotating();
    cv::Point top = topPointAfterRotating();
    //生成真目标选择区域和图像
    for(int i=0;i<this->poly.size();i++){
        this->poly[i]->x-=left.x;
        this->poly[i]->y-=top.y;
    }
    setPoly(this->poly);
    cv::Point left2 = this->leftPointAfterRotating();
    cv::Point right2 = rightPointAfterRotating();
    cv::Point top2 = topPointAfterRotating();
    cv::Point bottom2 = bottomPointAfterRotating();
    int regionwidth2 = right2.x-left2.x;
    int regionheigth2 = bottom2.y-top2.y;
    cv::Mat mat = cv::Mat(regionwidth2, regionheigth2, CV_8UC3, cv::Scalar(0, 0, 0));
    if(this->type == Region::TypeEllipse){
        //画旋转的椭圆
        cv::ellipse(mat,cv::Point(this->poly[0]->x+(this->poly[2]->x-this->poly[0]->x)/2,this->poly[0]->y+
                (this->poly[2]->y-this->poly[0]->y)/2),cv::Size((this->poly[2]->x-this->poly[0]->x)/2,(this->poly[2]->y
                -this->poly[0]->y)/2),this->Angle,0,360,cv::Scalar(0,0,255),2);
    }
    else{
        int size = poly.size();
        for(int i = 0; i < size - 1; i++){
            cv::Point p1 = cv::Point(poly[i].x, poly[i].y);
            cv::Point p2 = cv::Point(poly[i+1].x, poly[i+1].y);
            cv::line(mat,p1,p2,cv::Scalar(0,0,255),2);
        }
        cv::Point p1 = cv::Point(poly[size-1].x, poly[size-1].y);
        cv::Point p2 = cv::Point(poly[0].x, poly[0].y);
        cv::line(mat,p1,p2,cv::Scalar(0,0,255),2);
    }
    return mat;
}

cv::Mat Region::getSubMat(cv::Mat mat){
    cv::Point left = this->leftPointAfterRotating();
    cv::Point right = rightPointAfterRotating();
    cv::Point top = topPointAfterRotating();
    cv::Point bottom = bottomPointAfterRotating();
    int regionwidth = right.x-left.x;
    int regionheigth = bottom.y-top.y;
    cv::Point leftup = cv::Point(left.x,top.y);
    cv::Mat submat;
    mat(cv::Rect(leftup.x,leftup.y,regionwidth,regionheigth)).copyTo(submat);
    return submat;
}

void Region::setCentralPoint(cv::Point p, int width, int height){
    //Point* cp = this->centralPoint();
    if(this->poly.size()>0){
        int offsetx = p.x-cp->x;
        int offsety = p.y-cp->y;
        cv::Point* left = this->leftPoint();
        cv::Point* right = this->rightPoint();
        cv::Point* top = this->topPoint();
        cv::Point* bottom = this->bottomPoint();
        int regionwidth = right->x-left->x;
        int regionheight = bottom->y-top->y;
        while(width<regionwidth || height<regionheight){
            this->zoom(1/(1+SystemConfig::minRegionZoomFactor),width,height);
            left = this->leftPoint();
            right = this->rightPoint();
            top = this->topPoint();
            bottom = this->bottomPoint();
            regionwidth = right->x-left->x;
            regionheight = bottom->y-top->y;
        }
        this->move(offsetx,offsety,width,height);
    }
}

void Region::setCentralPoint2(cv::Point p, int width, int height){
    //Point* cp = this->centralPoint();
    cv::Point left = this->leftPointAfterRotating();
    cv::Point right = rightPointAfterRotating();
    cv::Point top = topPointAfterRotating();
    cv::Point bottom = bottomPointAfterRotating();
    int regionwidth = right.x-left.x;
    int regionheigth = bottom.y-top.y;
    cv::Point regioncentral = cv::Point(left.x+regionwidth/2, top.y+regionheigth/2);
    if(this->poly.size()>0){
        int offsetx = p.x-regioncentral.x;
        int offsety = p.y-regioncentral.y;
        this->move(offsetx,offsety);
        while(width<regionwidth || height<regionheigth || left.x<0||right.x>width||top.y<0||bottom.y>height){
            qDebug()<<"left.x="<<left.x<<";top.y="<<top.y<<";width="<<width<<";right.x="<<right.x<<";height="<<height<<";bottom.y="<<bottom.y<<";regionwidth="<<regionwidth<<";regionheight="<<regionheigth;
            this->zoom(1/(1+SystemConfig::minRegionZoomFactor));
            left = this->leftPointAfterRotating();
            right = rightPointAfterRotating();
            top = topPointAfterRotating();
            bottom = bottomPointAfterRotating();
            regionwidth = right.x-left.x;
            regionheigth = bottom.y-top.y;
        }
    }
}

void Region::setPoly(QVector<cv::Point *> poly){
    this->poly = poly;
    cp = this->centralPoint();
}

//平移
void Region::move(int offsetx, int offsety, int width, int heigh){
    if(poly.size()>0){
        for(int i = 0; i < poly.size(); i++){
            cv::Point* p = poly[i];
            p->x += offsetx;
            p->y += offsety;
            //qDebug()<<"from Region:"<<p->x<<p->y;
        }
        this->setPoly(this->poly);
        cv::Point* left = this->leftPoint();
        if(left->x<0){
            this->move(-left->x,0,width,heigh);
        }
        cv::Point* right = this->rightPoint();
        if(right->x>width){
            this->move(width-right->x,0,width,heigh);
        }
        cv::Point* top = this->topPoint();
        if(top->y<0){
            this->move(0,-top->y,width,heigh);
        }
        cv::Point* bottom = this->bottomPoint();
        if(bottom->y>heigh){
            this->move(0,heigh-bottom->y,width,heigh);
        }
    }
}

void Region::move(int offsetx, int offsety){
    if(poly.size()>0){
        for(int i = 0; i < poly.size(); i++){
            cv::Point* p = poly[i];
            p->x += offsetx;
            p->y += offsety;
            //qDebug()<<"from Region:"<<p->x<<p->y;
        }
        this->setPoly(this->poly);
    }
}

//旋转
void Region::rotate(cv::Point* p1, cv::Point* p2, int width, int heigh){
    double angle = this->getAngle(p1,p2);
    if(this->poly.size()>0){
        for(int i = 0; i<this->poly.size();i++){
            cv::Point* p = poly[i];
    //        double angle1 = qAsin((p1->y-cp->y)/sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y)));
    //        double angle2 = angle1 + angle;
    //        double x = cp->x + sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))*cos(angle2);
    //        double y = cp->y + sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))*sin(angle2);
            double x = cp->x + (p->x-cp->x)*cos(angle)-(p->y-cp->y)*sin(angle);
            double y = cp->y + (p->x-cp->x)*sin(angle)+(p->y-cp->y)*cos(angle);
    //        double x = cp->x + (p->x-cp->x)*cos(angle)+(p->y-cp->y)*sin(angle);
    //        double y = cp->y + (p->y-cp->y)*cos(angle)-(p->x-cp->x)*sin(angle);
            p->x = x;
            p->y = y;
        }
        cv::Point* left = this->leftPoint();
        if(left->x<0){
            this->move(-left->x,0,width,heigh);
        }
        cv::Point* right = this->rightPoint();
        if(right->x>width){
            this->move(width-right->x,0,width,heigh);
        }
        cv::Point* top = this->topPoint();
        if(top->y<0){
            this->move(0,-top->y,width,heigh);
        }
        cv::Point* bottom = this->bottomPoint();
        if(bottom->y>heigh){
            this->move(0,heigh-bottom->y,width,heigh);
        }
    }
    delete p1;
    delete p2;
}

//旋转2
void Region::rotate(double angle, int width, int heigh){
    if(this->poly.size()>0){
        for(int i = 0; i<this->poly.size();i++){
            cv::Point* p = poly[i];
    //        double angle1 = qAsin((p1->y-cp->y)/sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y)));
    //        double angle2 = angle1 + angle;
    //        double x = cp->x + sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))*cos(angle2);
    //        double y = cp->y + sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))*sin(angle2);
            double x = cp->x + (p->x-cp->x)*cos(angle)-(p->y-cp->y)*sin(angle);
            double y = cp->y + (p->x-cp->x)*sin(angle)+(p->y-cp->y)*cos(angle);
    //        double x = cp->x + (p->x-cp->x)*cos(angle)+(p->y-cp->y)*sin(angle);
    //        double y = cp->y + (p->y-cp->y)*cos(angle)-(p->x-cp->x)*sin(angle);
            p->x = x;
            p->y = y;
        }
        cv::Point* left = this->leftPoint();
        if(left->x<0){
            this->move(-left->x,0,width,heigh);
        }
        cv::Point* right = this->rightPoint();
        if(right->x>width){
            this->move(width-right->x,0,width,heigh);
        }
        cv::Point* top = this->topPoint();
        if(top->y<0){
            this->move(0,-top->y,width,heigh);
        }
        cv::Point* bottom = this->bottomPoint();
        if(bottom->y>heigh){
            this->move(0,heigh-bottom->y,width,heigh);
        }
    }
}

//旋转3
cv::Point Region::rotate(cv::Point p){
    double angle = this->Angle*M_PI/180;
    double x = cp->x + (p.x-cp->x)*cos(-angle)-(p.y-cp->y)*sin(-angle);
    double y = cp->y + (p.x-cp->x)*sin(-angle)+(p.y-cp->y)*cos(-angle);
    return cv::Point(x,y);
}
//旋转4
//旋转2
void Region::rotate(int width, int heigh){
    if(this->poly.size()>0){
        //double angle = this->Angle*M_PI/180;
//        for(int i = 0; i<this->poly.size();i++){
//            cv::Point* p = poly[i];
//            double x = cp->x + (p->x-cp->x)*cos(angle)-(p->y-cp->y)*sin(angle);
//            double y = cp->y + (p->x-cp->x)*sin(angle)+(p->y-cp->y)*cos(angle);
//            p->x = x;
//            p->y = y;
//        }

        cv::Point left = this->leftPointAfterRotating();
        if(left.x<0){
            this->move(-left.x,0,width,heigh);
        }
        cv::Point right = this->rightPointAfterRotating();
        if(right.x>width){
            this->move(width-right.x,0,width,heigh);
        }
        cv::Point top = this->topPointAfterRotating();
        if(top.y<0){
            this->move(0,-top.y,width,heigh);
        }
        cv::Point bottom = this->bottomPointAfterRotating();
        if(bottom.y>heigh){
            this->move(0,heigh-bottom.y,width,heigh);
        }
        //this->Angle = 0;
    }
}

QVector<cv::Point> Region::getPolyAfterRotating(){
    QVector<cv::Point> ps;
    double angle = this->Angle*M_PI/180;
    for(int i = 0; i<this->poly.size();i++){
        cv::Point* p = poly[i];
        double x = cp->x + (p->x-cp->x)*cos(angle)-(p->y-cp->y)*sin(angle);
        double y = cp->y + (p->x-cp->x)*sin(angle)+(p->y-cp->y)*cos(angle);
        ps.push_back(cv::Point(x,y));
    }
    return ps;
}

void Region::setRotateAngle(double angle){
    this->Angle = angle;
}

//缩放
void Region::zoom(double factor, int width, int heigh){
    //Point* cp = this->centralPoint();
    if(this->poly.size()>0){
        for(int i = 0; i<this->poly.size();i++){
            cv::Point* p1 = poly[i];
    //        double angle = qAsin((p1->y-cp->y)/sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y)));
    //        double x = cp->x + (sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))+factor)*cos(angle);
    //        double y = cp->y + (sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))+factor)*sin(angle);
            double x = p1->x*factor+cp->x*(1-factor);
            double y = p1->y*factor+cp->y*(1-factor);
            p1->x = x;
            p1->y = y;
        }
        cv::Point* left = this->leftPoint();
        cv::Point* right = this->rightPoint();
        cv::Point* top = this->topPoint();
        cv::Point* bottom = this->bottomPoint();
        if((right->x-left->x)>width||(bottom->y-top->y)>heigh){
            if(factor>1){
                this->zoom(1/(1+SystemConfig::minRegionZoomFactor),width,heigh);
            }
            else {
                this->zoom(factor,width,heigh);
            }
        }

        if(left->x<0){
            this->move(-left->x,0,width,heigh);
        }

        if(right->x>width){
            this->move(width-right->x,0,width,heigh);
        }

        if(top->y<0){
            this->move(0,-top->y,width,heigh);
        }

        if(bottom->y>heigh){
            this->move(0,heigh-bottom->y,width,heigh);
        }
    }
}

void Region::zoom(double factor){
    //Point* cp = this->centralPoint();
    if(this->poly.size()>0){
        for(int i = 0; i<this->poly.size();i++){
            cv::Point* p1 = poly[i];
    //        double angle = qAsin((p1->y-cp->y)/sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y)));
    //        double x = cp->x + (sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))+factor)*cos(angle);
    //        double y = cp->y + (sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y))+factor)*sin(angle);
            double x = p1->x*factor+cp->x*(1-factor);
            double y = p1->y*factor+cp->y*(1-factor);
            p1->x = x;
            p1->y = y;
        }
    }
}

double Region::getAngle(cv::Point* p1, cv::Point* p2){
    //Point* cp = this->centralPoint();
    double angle1 = qAsin((p1->y-cp->y)/sqrt((p1->x-cp->x)*(p1->x-cp->x)+(p1->y-cp->y)*(p1->y-cp->y)));
    double angle2 = qAsin((p2->y-cp->y)/sqrt((p2->x-cp->x)*(p2->x-cp->x)+(p2->y-cp->y)*(p2->y-cp->y)));
    return 180*(angle2-angle1)/M_PI;
    delete p1;
    delete p2;
}

bool Region::isInner(cv::Point p){
    bool in = false;
    if(this->type==Region::TypeRect||this->type==Region::TypePoly){
        QVector<cv::Point> poly = this->getPolyAfterRotating();
        int inner = cv::pointPolygonTest(poly.toStdVector(), p, false);
        if (inner >= 0){
            in = true;
            this->isSelected = true;
        }
        else{
            in = false;
            this->isSelected = false;
        }
    }
    else{
        cv::Point p2 = this->rotate(p);
        double x = p2.x;
        double y = p2.y;
        double a,b,c;//椭圆的长半轴和短半轴,焦半轴
        a=(double)abs(((poly[2]->x-poly[0]->x)/2));//长半轴
        b=(double)abs(((poly[2]->y-poly[0]->y)/2));//短半轴
        double DMax;
        double d1,d2;//当前点到两个焦点的距离
        double CenterPotX,CenterPotY;//中心点的坐标分量
        CenterPotX=(double)((poly[2]->x+poly[0]->x)/2);
        CenterPotY=(double)((poly[2]->y+poly[0]->y)/2);
        if(a>=b){
            c=(double)sqrt(a*a-b*b);//焦半轴
            d1=(double)sqrt((x-CenterPotX+c)*(x-CenterPotX+c)+(y-CenterPotY)*(y-CenterPotY));//到左焦点的距离
            d2=(double)sqrt((x-CenterPotX-c)*(x-CenterPotX-c)+(y-CenterPotY)*(y-CenterPotY));//到右焦点的距离
            DMax=(double)abs(2*a);
        }
        if(a<b){
            c=(double)sqrt(b*b-a*a);//焦半轴
            d1=(double)sqrt((x-CenterPotX)*(x-CenterPotX)+(y-CenterPotY+c)*(y-CenterPotY+c));//到左焦点的距离
            d2=(double)sqrt((x-CenterPotX)*(x-CenterPotX)+(y-CenterPotY-c)*(y-CenterPotY-c));//到右焦点的距离
            DMax=(double)abs(2*b);
        }
        in = (d1+d2<DMax);
        this->isSelected = in;
    }
    return in;
}

cv::Point* Region::leftPoint(){
    int size = poly.size();
    if(size>0){
        int minX = poly[0]->x;
        cv::Point* left = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i]->x<minX){
                minX=poly[i]->x;
                left=poly[i];
            }
        }
        return left;
    }
    else{
        return new cv::Point(0,0);
    }
}

cv::Point* Region::rightPoint(){
    int size = poly.size();
    if(size>0){
        int maxX = poly[0]->x;
        cv::Point* right = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i]->x>maxX){
                maxX=poly[i]->x;
                right=poly[i];
            }
        }
        return right;
    }
    else{
        return new cv::Point(0,0);
    }
}

cv::Point* Region::topPoint(){
    int size = poly.size();
    if(size>0){
        int minY = poly[0]->y;
        cv::Point* top = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i]->y<minY){
                minY=poly[i]->y;
                top=poly[i];
            }
        }
        return top;
    }
    else{
        return new cv::Point(0,0);
    }
}

cv::Point* Region::bottomPoint(){
    int size = poly.size();
    if(size>0){
        int maxY = poly[0]->y;
        cv::Point* bottom = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i]->y>maxY){
                maxY=poly[i]->y;
                bottom=poly[i];
            }
        }
        return bottom;
    }
    else{
        return new cv::Point(0,0);
    }
}

cv::Point* Region::centralPoint(){
    int size = poly.size();
    if(size>0){
        int sumX = 0;
        int sumY = 0;
        for(int i = 0;i<size;i++){
            sumX+=poly[i]->x;
            sumY+=poly[i]->y;
        }
        return new cv::Point(sumX/size,sumY/size);
    }
    else{
        return new cv::Point(0,0);
    }
}

cv::Point Region::leftPoint(QVector<cv::Point> poly){
    int size = poly.size();
    if(size>0){
        int minX = poly[0].x;
        cv::Point left = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].x<minX){
                minX=poly[i].x;
                left=poly[i];
            }
        }
        return left;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::rightPoint(QVector<cv::Point> poly){
    int size = poly.size();
    if(size>0){
        int maxX = poly[0].x;
        cv::Point right = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].x>maxX){
                maxX=poly[i].x;
                right=poly[i];
            }
        }
        return right;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::topPoint(QVector<cv::Point> poly){
    int size = poly.size();
    if(size>0){
        int minY = poly[0].y;
        cv::Point top = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].y<minY){
                minY=poly[i].y;
                top=poly[i];
            }
        }
        return top;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::bottomPoint(QVector<cv::Point> poly){
    int size = poly.size();
    if(size>0){
        int maxY = poly[0].y;
        cv::Point bottom = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].y>maxY){
                maxY=poly[i].y;
                bottom=poly[i];
            }
        }
        return bottom;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::centralPoint(QVector<cv::Point> poly){
    int size = poly.size();
    if(size>0){
        int sumX = 0;
        int sumY = 0;
        for(int i = 0;i<size;i++){
            sumX+=poly[i].x;
            sumY+=poly[i].y;
        }
        return cv::Point(sumX/size,sumY/size);
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::leftPointAfterRotating(){
    QVector<cv::Point> poly = this->getPolyAfterRotating();
    int size = poly.size();
    if(size>0){
        int minX = poly[0].x;
        cv::Point left = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].x<minX){
                minX=poly[i].x;
                left=poly[i];
            }
        }
        return left;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::rightPointAfterRotating(){
    QVector<cv::Point> poly = this->getPolyAfterRotating();
    int size = poly.size();
    if(size>0){
        int maxX = poly[0].x;
        cv::Point right = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].x>maxX){
                maxX=poly[i].x;
                right=poly[i];
            }
        }
        return right;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::topPointAfterRotating(){
    QVector<cv::Point> poly = this->getPolyAfterRotating();
    int size = poly.size();
    if(size>0){
        int minY = poly[0].y;
        cv::Point top = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].y<minY){
                minY=poly[i].y;
                top=poly[i];
            }
        }
        return top;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::bottomPointAfterRotating(){
    QVector<cv::Point> poly = this->getPolyAfterRotating();
    int size = poly.size();
    if(size>0){
        int maxY = poly[0].y;
        cv::Point bottom = poly[0];
        for(int i = 1;i<size;i++){
            if(poly[i].y>maxY){
                maxY=poly[i].y;
                bottom=poly[i];
            }
        }
        return bottom;
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Point Region::centralPointAfterRotating(){
    QVector<cv::Point> poly = this->getPolyAfterRotating();
    int size = poly.size();
    if(size>0){
        int sumX = 0;
        int sumY = 0;
        for(int i = 0;i<size;i++){
            sumX+=poly[i].x;
            sumY+=poly[i].y;
        }
        return cv::Point(sumX/size,sumY/size);
    }
    else{
        return cv::Point(0,0);
    }
}

cv::Rect Region::getRectAfterRotating(){
    cv::Point left = this->leftPointAfterRotating();
    cv::Point right = this->rightPointAfterRotating();
    cv::Point top = this->topPointAfterRotating();
    cv::Point bottom = this->bottomPointAfterRotating();
    return cv::Rect(0,0,right.x-left.x,bottom.y-top.y);
}

QVector<cv::Point*> Region::getPoly(){
    return poly;
}

QString Region::generateID(){
    return "Region_" + QUuid::createUuid().toString().remove("{").remove("}").remove("-");
}

QVector<cv::Point> Region::clonePoly(){
    QVector<cv::Point> temppoly;
    for(int i=0;i<poly.size();i++){
        cv::Point p = cv::Point(poly[i]->x,poly[i]->y);
        temppoly.push_back(p);
    }
    return temppoly;
}

//void Region::insertIntoDB(){
//    QSqlDatabase db = Utils::getDB();
//    if(!db.isOpen()) db.open();
//    QSqlQuery query(db);
//    query.prepare(QString("INSERT INTO %1(DataID,RegionName,ObjID,ObjType,VNum,X,Y,Angle,TTime,Intro)"
//                              "VALUES (:dataid, :regionName,:objID,:objType,:vNum,:x,:y,:angle,:time,:intro)").arg(Region::Table_Name));
//    this->VNum=this->poly.size();
//    this->X="";
//    this->Y="";
//    this->ObjType=this->type;
//    for (int i=0;i<this->poly.size();i++) {
//        this->X+="+"+QString::number(poly[i]->x);
//        this->Y+="+"+QString::number(poly[i]->y);
//    }
////    query.bindValue(":Dataid", Region::DataID_Name);
////    query.bindValue(":RegionName", Region::RegionName_Name);
////    query.bindValue(":ObjID", Region::ObjID_Name);
////    query.bindValue(":ObjType", Region::ObjType_Name);
////    query.bindValue(":VNum", Region::VNum_Name);
////    query.bindValue(":X", Region::X_Name);
////    query.bindValue(":Y", Region::Y_Name);
////    query.bindValue(":Angle", Region::Angle_Name);
////    query.bindValue(":Time", Region::Time_Name);
////    query.bindValue(":Intro", Region::Intro_Name);
//    query.bindValue(":dataid", this->DataID);
//    query.bindValue(":regionName", this->RegionName);
//    query.bindValue(":objID", this->ObjID);
//    query.bindValue(":objType", this->ObjType);
//    query.bindValue(":vNum", this->VNum);
//    query.bindValue(":time", this->Time.toString("dd.MM.yyyy hh:mm:ss.zzz"));
//    query.bindValue(":x", this->X);
//    query.bindValue(":y", this->Y);
//    query.bindValue(":angle", this->Angle);
//    query.bindValue(":intro", this->Intro);
//    query.exec();
//    //if(db.isOpen()) db.close();
//}

//void Region::updateDB(){
//    QSqlDatabase db = Utils::getDB();
//    if(!db.isOpen()) db.open();
//    QSqlQuery query(db);
//    query.prepare(QString("UPDATE %1 SET RegionName=regionName,ObjID=:objID,ObjType=:objType,VNum=:vNum,X=:x,Y=:y,Angle=:angle,TTime=:time,Intro=:intro"
//                              "where DataID=:dataid").arg(Region::Table_Name));
//    this->VNum=this->poly.size();
//    this->X="";
//    this->Y="";
//    this->ObjType=this->type;
//    for (int i=0;i<this->poly.size();i++) {
//        this->X+="+"+QString::number(poly[i]->x);
//        this->Y+="+"+QString::number(poly[i]->y);
//    }
////    query.bindValue(":Dataid", Region::DataID_Name);
////    query.bindValue(":RegionName", Region::RegionName_Name);
////    query.bindValue(":ObjID", Region::ObjID_Name);
////    query.bindValue(":ObjType", Region::ObjType_Name);
////    query.bindValue(":VNum", Region::VNum_Name);
////    query.bindValue(":X", Region::X_Name);
////    query.bindValue(":Y", Region::Y_Name);
////    query.bindValue(":Angle", Region::Angle_Name);
////    query.bindValue(":Time", Region::Time_Name);
////    query.bindValue(":Intro", Region::Intro_Name);
//    query.bindValue(":dataid", this->DataID);
//    query.bindValue(":regionName", this->RegionName);
//    query.bindValue(":objID", this->ObjID);
//    query.bindValue(":objType", this->ObjType);
//    query.bindValue(":vNum", this->VNum);
//    query.bindValue(":time", this->Time.toString("dd.MM.yyyy hh:mm:ss.zzz"));
//    query.bindValue(":x", this->X);
//    query.bindValue(":y", this->Y);
//    query.bindValue(":angle", this->Angle);
//    query.bindValue(":intro", this->Intro);
//    query.exec();
//    //if(db.isOpen()) db.close();
//}

//void Region::deleteFromDB(){
//    QSqlDatabase db = Utils::getDB();
//    if(!db.isOpen()) db.open();
//    QSqlQuery query(db);
//    query.prepare(QString("DELETE FROM %1 "
//                              "where DataID=:dataid").arg(Region::Table_Name));
////    query.bindValue(":Dataid", Region::DataID_Name);
//    query.bindValue(":dataid", this->DataID);
//    query.exec();
//    //if(db.isOpen()) db.close();
//}

//void Region::deleteFromDB(QString id){
//    QSqlDatabase db = Utils::getDB();
//    if(!db.isOpen()) db.open();
//    QSqlQuery query(db);
//    query.prepare(QString("DELETE FROM %1 "
//                              "where DataID=:dataid").arg(Region::Table_Name));
////    query.bindValue(":Dataid", Region::DataID_Name);
//    query.bindValue(":dataid", id);
//    query.exec();
//    //if(db.isOpen()) db.close();
//}

//void Region::selectFromDB(QString id){
//    QSqlDatabase db = Utils::getDB();
//    if(!db.isOpen()) db.open();
//    QSqlQuery query(db);
//    query.prepare(QString("SELECT * FROM %1 "
//                              "where DataID=:dataid").arg(Region::Table_Name));
////    query.bindValue(":Dataid", Region::DataID_Name);
//    query.bindValue(":dataid", id);
//    query.exec();
//    while (query.next()){
//        this->DataID=query.value(0).toString();
//        this->RegionName=query.value(1).toString();
//        this->ObjID=query.value(2).toString();
//        this->ObjType=query.value(3).toBool();
//        this->VNum=query.value(4).toInt();
//        this->X=query.value(5).toString();
//        this->Y=query.value(6).toString();
//        this->Angle=query.value(7).toDouble();
//        this->Time=QDateTime::fromString(query.value(8).toString(),"dd.MM.yyyy hh:mm:ss.zzz");
//        this->Intro=query.value(9).toString();
//    }
//    //if(db.isOpen()) db.close();
//    QStringList xlist = this->X.split("+");
//    QStringList ylist = this->Y.split("+");
//    for (int i=0;i<this->poly.size();i++) {
//        cv::Point* p = poly[i];
//        delete p;
//    }
//    this->poly.clear();
//    for (int i=1;i<xlist.size();i++) {
//        int x = xlist[i].toInt();
//        int y = ylist[i].toInt();
//        cv::Point* p = new cv::Point(x,y);
//        poly.push_back(p);
//    }
//    this->setPoly(this->poly);
//    this->type=this->ObjType;
//}
