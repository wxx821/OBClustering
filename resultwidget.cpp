#include "resultwidget.h"
#include <QStringList>
#include <QHeaderView>
#include <QList>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QEventLoop>
#include "utils.h"
#include "Word/reportutils.h"
#include "waitingdialog.h"

ResultWidget::ResultWidget(QWidget *parent) : QWidget(parent)
{
    this->region1 = nullptr;
    this->region2 = nullptr;

    table1 = new QTableWidget(this);
    table1->setRowCount(4);
    table1->setColumnCount(2);
    QStringList header1;
    header1<<"相似度"<<"相似度值";
    //table1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table1->setHorizontalHeaderLabels(header1);
    table1->setItem(0, 0, new QTableWidgetItem("灰度相似度"));
    table1->setItem(1, 0, new QTableWidgetItem("色度相似度"));
    table1->setItem(2, 0, new QTableWidgetItem("纹理相似度"));
    table1->setItem(3, 0, new QTableWidgetItem("斑块特征相似度"));
    degree1 = new QTableWidgetItem("0");
    degree2 = new QTableWidgetItem("0");
    degree3 = new QTableWidgetItem("0");
    degree4 = new QTableWidgetItem("0");
    table1->setItem(0, 1, degree1);
    table1->setItem(1, 1, degree2);
    table1->setItem(2, 1, degree3);
    table1->setItem(3, 1, degree4);
    cb1 = new QCheckBox(this);
    cb1->setText("显示区1选择区域内");
    cb1->setChecked(true);
    cb2 = new QCheckBox(this);
    cb2->setText("显示区2选择区域内");
    cb2->setChecked(true);
    pbRefresh2 = new QPushButton(this);
    pbRefresh2->setText("刷新");
    connect(pbRefresh2, SIGNAL(clicked()), this, SLOT(datarefresh2()));
    lay1 = new QGridLayout(this);
    lay1->addWidget(table1,0,0,1,2);
    lay1->addWidget(cb1,1,0,1,1);
    lay1->addWidget(cb2,1,1,1,1);
    lay1->addWidget(pbRefresh2,2,0,1,2);
    table1widget = new QWidget(this);
    table1widget->setLayout(lay1);

    table2 = new QTableWidget(this);
    table2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table2->setColumnCount(5);
    //table2->setRowCount(2);
    QStringList header2;
    header2<<"评估名称"<<"评估类别"<<"评估对象"<<"相似度"<<"相似度值";
    table2->setHorizontalHeaderLabels(header2);

    pbRefresh = new QPushButton(this);
    pbRefresh->setText("刷新");
    connect(pbRefresh, SIGNAL(clicked()), this, SLOT(datarefresh()));
    pbGenerateReport = new QPushButton(this);
    pbGenerateReport->setText("生成报告");
    connect(pbGenerateReport, SIGNAL(clicked()), this, SLOT(generatereport()));
    lay2 = new QGridLayout(this);
    lay2->addWidget(table2,0,0,1,2);
    lay2->addWidget(pbRefresh,1,0,1,1);
    lay2->addWidget(pbGenerateReport,1,1,1,1);
    table2widget = new QWidget(this);
    table2widget->setLayout(lay2);
    tabw = new QTabWidget(this);
    tabw->addTab(table1widget,"显示区");
    tabw->addTab(table2widget,"总体");
    lay = new QGridLayout(this);
    lay->addWidget(tabw,0,0);
    this->setLayout(lay);
    //tabw->resize(this->width(),this->height());
}

ResultWidget::~ResultWidget(){
//    delete degree1;
//    delete degree2;
//    delete degree3;
//    delete degree4;
//    delete table1;
//    delete cb1;
//    delete cb2;
//    delete table2;
//    delete pbRefresh;
//    delete pbGenerateReport;
//    delete lay1;
//    delete lay2;
//    delete table1widget;
//    delete table2widget;
//    delete tabw;
//    delete lay;
}

void ResultWidget::setData(DataModel* dm){
    this->data = dm;
    //this->datarefresh();
}

void ResultWidget::setMat1(cv::Mat mat1, Region* region1){
    this->mat1 = mat1;
    this->region1 = region1;
}

void ResultWidget::setMat2(cv::Mat mat2, Region* region2){
    this->mat2 = mat2;
    this->region2 = region2;
}

void ResultWidget::resizeEvent(QResizeEvent *e){
//    tabw->resize(this->width(),this->height());
    //table1->resize(this->width(),this->height());
    //table2->resize(this->width(),this->height());
}

void ResultWidget::datarefresh2(){
    if(!this->mat1.empty() && !this->mat2.empty()){
        WaitingDialog* wd = new WaitingDialog(this);
        wd->setLText("正在计算所两个显示区图像的相似度，需要若干秒的时间，请耐心等候......");
        wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
        wd->setFixedWidth(QApplication::desktop()->width()/2);
        wd->setFixedHeight(QApplication::desktop()->height()/10);
        wd->setModal(true);
        wd->show();
        wd->l->repaint();
        QEventLoop loop;//定义一个新的事件循环
        QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
        loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
        double deg1 = 0;
        double deg2 = 0;
        double deg3 = 0;
        double deg4 = 0;
        if(this->cb1->isChecked() && this->cb2->isChecked()){
            deg1 = Utils::getGrayDegree(this->mat1,this->region1,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的灰度相似度
            deg2 = Utils::getToneDegree(this->mat1,this->region1,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的色度相似度
            deg3 = Utils::getTextureDegree(this->mat1,this->region1,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的纹理相似度
            deg4 = Utils::getFeatureDegree(this->mat1,this->region1,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的斑块特征相似度
        }
        else if(!this->cb1->isChecked() && this->cb2->isChecked()){
            deg1 = Utils::getGrayDegree(this->mat1,nullptr,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的灰度相似度
            deg2 = Utils::getToneDegree(this->mat1,nullptr,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的色度相似度
            deg3 = Utils::getTextureDegree(this->mat1,nullptr,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的纹理相似度
            deg4 = Utils::getFeatureDegree(this->mat1,nullptr,this->mat2,this->region2);//调用图像处理函数，计算mat1和mat2的斑块特征相似度
        }
        else if(this->cb1->isChecked() && !this->cb2->isChecked()){
            deg1 = Utils::getGrayDegree(this->mat1,this->region1,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的灰度相似度
            deg2 = Utils::getToneDegree(this->mat1,this->region1,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的色度相似度
            deg3 = Utils::getTextureDegree(this->mat1,this->region1,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的纹理相似度
            deg4 = Utils::getFeatureDegree(this->mat1,this->region1,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的斑块特征相似度
        }
        else{
            deg1 = Utils::getGrayDegree(this->mat1,nullptr,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的灰度相似度
            deg2 = Utils::getToneDegree(this->mat1,nullptr,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的色度相似度
            deg3 = Utils::getTextureDegree(this->mat1,nullptr,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的纹理相似度
            deg4 = Utils::getFeatureDegree(this->mat1,nullptr,this->mat2,nullptr);//调用图像处理函数，计算mat1和mat2的斑块特征相似度
        }
        this->degree1->setText(QString::number(deg1));
        this->degree2->setText(QString::number(deg2));
        this->degree3->setText(QString::number(deg3));
        this->degree4->setText(QString::number(deg4));
        wd->close();
        delete wd;
    }
}

void ResultWidget::datarefresh(){
//    table2->clear();
//    WaitingDialog* wd = new WaitingDialog(this);
//    wd->setLText("正在计算所涉及评估的图像之间的相似性，需要几分钟的时间，请耐心等候......");
//    wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
//    wd->setFixedWidth(QApplication::desktop()->width()/2);
//    wd->setFixedHeight(QApplication::desktop()->height()/10);
//    wd->setModal(true);
//    wd->show();
//    wd->l->repaint();
//    QEventLoop loop;//定义一个新的事件循环
//    QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
//    data->computeDegrees();
//    wd->close();
//    delete wd;
//    QList<Assess*> assesses = data->getAssesses();
//    int asize = assesses.size();
//    int rowcount = 0;
//    for(int i=0;i<asize;i++){
//        Assess* assess = assesses[i];
//        if(assess->OpticesID!=""){
//            rowcount += 9*4;
//        }
//        if(assess->InfraredID!=""){
//            rowcount += 9*4;
//        }
//        if(assess->SARID!=""){
//            rowcount += 9*4;
//        }
//    }
//    QStringList header2;
//    header2<<"评估名称"<<"评估类别"<<"评估对象"<<"相似度"<<"相似度值";
//    table2->setHorizontalHeaderLabels(header2);
//    table2->setColumnCount(5);
//    table2->setRowCount(rowcount);
//    rowcount = -1;
//    for(int i=0;i<asize;i++){
//        Assess* assess = assesses[i];
//        int rowcount2 = 0;
//        if(assess->OpticesID!=""){
//            OpticesAssess* oa = data->getOpticesAssess(assess->OpticesID);
//            double deg11 = oa->Gray_TF;
//            double deg12 = oa->Tone_TF;
//            double deg13 = oa->Texture_TF;
//            double deg14 = oa->Feature_TF;
//            double deg21 = oa->Gray_TFill;
//            double deg22 = oa->Tone_TFill;
//            double deg23 = oa->Texture_TFill;
//            double deg24 = oa->Feature_TFill;
//            double deg31 = oa->Gray_FFill;
//            double deg32 = oa->Tone_FFill;
//            double deg33 = oa->Texture_FFill;
//            double deg34 = oa->Feature_FFill;
//            double deg41 = oa->Gray_FillB;
//            double deg42 = oa->Tone_FillB;
//            double deg43 = oa->Texture_FillB;
//            double deg44 = oa->Feature_FillB;
//            double deg51 = oa->Gray_TB;
//            double deg52 = oa->Tone_TB;
//            double deg53 = oa->Texture_TB;
//            double deg54 = oa->Feature_TB;
//            double deg61 = oa->Gray_FB;
//            double deg62 = oa->Tone_FB;
//            double deg63 = oa->Texture_FB;
//            double deg64 = oa->Feature_FB;
//            double deg71 = oa->Gray_TBFB;
//            double deg72 = oa->Tone_TBFB;
//            double deg73 = oa->Texture_TBFB;
//            double deg74 = oa->Feature_TBFB;
//            double deg81 = oa->Gray_TBFillB;
//            double deg82 = oa->Tone_TBFillB;
//            double deg83 = oa->Texture_TBFillB;
//            double deg84 = oa->Feature_TBFillB;
//            double deg91 = oa->Gray_FBFillB;
//            double deg92 = oa->Tone_FBFillB;
//            double deg93 = oa->Texture_FBFillB;
//            double deg94 = oa->Feature_FBFillB;
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem(assess->AName));
//            table2->setItem(rowcount,1,new QTableWidgetItem("光学评估"));
//            table2->setItem(rowcount,2,new QTableWidgetItem("真假目标"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg11)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg12)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg13)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg14)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //真目标与回填图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("真与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg21)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg22)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg23)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg24)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //示假目标与回填图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("假与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg31)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg32)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg33)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg34)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //回填图像与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("回填与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg41)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg42)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg43)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg44)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //真目标与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("真与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg51)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg52)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg53)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg54)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //示假目标与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("假与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg61)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg62)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg63)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg64)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含真目标和示假目标的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含真与假"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg71)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg72)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg73)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg74)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含真目标的图像和包含回填的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含真与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg81)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg82)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg83)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg84)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含示假目标的图像与包含回填的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含假与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg91)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg92)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg93)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg94)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            table2->setSpan(rowcount-9*4+1,1,9*4,1);
//        }
//        if(assess->InfraredID!=""){
//            InfraredAssess* ia = data->getInfraredAssess(assess->InfraredID);
//            rowcount++;
//            rowcount2++;
//            double deg11 = ia->Gray_TF;
//            double deg12 = ia->Tone_TF;
//            double deg13 = ia->Texture_TF;
//            double deg14 = ia->Feature_TF;
//            double deg21 = ia->Gray_TFill;
//            double deg22 = ia->Tone_TFill;
//            double deg23 = ia->Texture_TFill;
//            double deg24 = ia->Feature_TFill;
//            double deg31 = ia->Gray_FFill;
//            double deg32 = ia->Tone_FFill;
//            double deg33 = ia->Texture_FFill;
//            double deg34 = ia->Feature_FFill;
//            double deg41 = ia->Gray_FillB;
//            double deg42 = ia->Tone_FillB;
//            double deg43 = ia->Texture_FillB;
//            double deg44 = ia->Feature_FillB;
//            double deg51 = ia->Gray_TB;
//            double deg52 = ia->Tone_TB;
//            double deg53 = ia->Texture_TB;
//            double deg54 = ia->Feature_TB;
//            double deg61 = ia->Gray_FB;
//            double deg62 = ia->Tone_FB;
//            double deg63 = ia->Texture_FB;
//            double deg64 = ia->Feature_FB;
//            double deg71 = ia->Gray_TBFB;
//            double deg72 = ia->Tone_TBFB;
//            double deg73 = ia->Texture_TBFB;
//            double deg74 = ia->Feature_TBFB;
//            double deg81 = ia->Gray_TBFillB;
//            double deg82 = ia->Tone_TBFillB;
//            double deg83 = ia->Texture_TBFillB;
//            double deg84 = ia->Feature_TBFillB;
//            double deg91 = ia->Gray_FBFillB;
//            double deg92 = ia->Tone_FBFillB;
//            double deg93 = ia->Texture_FBFillB;
//            double deg94 = ia->Feature_FBFillB;
//            //真假目标之间的相似度
//            if(assess->OpticesID==""){
//                table2->setItem(rowcount,0,new QTableWidgetItem(assess->AName));
//            }
//            else{
//                table2->setItem(rowcount,0,new QTableWidgetItem());
//            }
//            table2->setItem(rowcount,1,new QTableWidgetItem("红外评估"));
//            table2->setItem(rowcount,2,new QTableWidgetItem("真假目标"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg11)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg12)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg13)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg14)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //真目标与回填图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("真与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg21)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg22)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg23)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg24)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //示假目标与回填图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("假与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg31)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg32)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg33)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg34)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //回填图像与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("回填与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg41)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg42)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg43)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg44)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //真目标与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("真与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg51)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg52)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg53)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg54)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //示假目标与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("假与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg61)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg62)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg63)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg64)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含真目标和示假目标的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含真与假"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg71)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg72)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg73)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg74)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含真目标的图像和包含回填的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含真与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg81)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg82)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg83)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg84)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含示假目标的图像与包含回填的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含假与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg91)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg92)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg93)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg94)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            table2->setSpan(rowcount-9*4+1,1,9*4,1);
//        }
//        if(assess->SARID!=""){
//            SARAssess* sa = data->getSARAssess(assess->SARID);
//            rowcount++;
//            rowcount2++;
//            double deg11 = sa->Gray_TF;
//            double deg12 = sa->Tone_TF;
//            double deg13 = sa->Texture_TF;
//            double deg14 = sa->Feature_TF;
//            double deg21 = sa->Gray_TFill;
//            double deg22 = sa->Tone_TFill;
//            double deg23 = sa->Texture_TFill;
//            double deg24 = sa->Feature_TFill;
//            double deg31 = sa->Gray_FFill;
//            double deg32 = sa->Tone_FFill;
//            double deg33 = sa->Texture_FFill;
//            double deg34 = sa->Feature_FFill;
//            double deg41 = sa->Gray_FillB;
//            double deg42 = sa->Tone_FillB;
//            double deg43 = sa->Texture_FillB;
//            double deg44 = sa->Feature_FillB;
//            double deg51 = sa->Gray_TB;
//            double deg52 = sa->Tone_TB;
//            double deg53 = sa->Texture_TB;
//            double deg54 = sa->Feature_TB;
//            double deg61 = sa->Gray_FB;
//            double deg62 = sa->Tone_FB;
//            double deg63 = sa->Texture_FB;
//            double deg64 = sa->Feature_FB;
//            double deg71 = sa->Gray_TBFB;
//            double deg72 = sa->Tone_TBFB;
//            double deg73 = sa->Texture_TBFB;
//            double deg74 = sa->Feature_TBFB;
//            double deg81 = sa->Gray_TBFillB;
//            double deg82 = sa->Tone_TBFillB;
//            double deg83 = sa->Texture_TBFillB;
//            double deg84 = sa->Feature_TBFillB;
//            double deg91 = sa->Gray_FBFillB;
//            double deg92 = sa->Tone_FBFillB;
//            double deg93 = sa->Texture_FBFillB;
//            double deg94 = sa->Feature_FBFillB;
//            //真假目标之间的相似度
//            if(assess->OpticesID=="" && assess->InfraredID==""){
//                table2->setItem(rowcount,0,new QTableWidgetItem(assess->AName));
//            }
//            else{
//                table2->setItem(rowcount,0,new QTableWidgetItem());
//            }
//            table2->setItem(rowcount,1,new QTableWidgetItem("SAR评估"));
//            table2->setItem(rowcount,2,new QTableWidgetItem("真假目标"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg11)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg12)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg13)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg14)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //真目标与回填图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("真与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg21)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg22)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg23)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg24)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //示假目标与回填图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("假与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg31)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg32)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg33)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg34)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //回填图像与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("回填与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg41)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg42)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg43)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg44)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //真目标与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("真与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg51)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg52)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg53)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg54)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //示假目标与背景之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("假与背景"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg61)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg62)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg63)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg64)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含真目标和示假目标的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含真与假"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg71)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg72)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg73)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg74)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含真目标的图像和包含回填的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含真与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg81)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg82)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg83)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg84)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            //包含示假目标的图像与包含回填的图像之间的相似度
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem("包含假与回填"));
//            table2->setItem(rowcount,3,new QTableWidgetItem("灰度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg91)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("色度相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg92)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("纹理相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg93)));
//            rowcount++;
//            rowcount2++;
//            table2->setItem(rowcount,0,new QTableWidgetItem());
//            table2->setItem(rowcount,1,new QTableWidgetItem());
//            table2->setItem(rowcount,2,new QTableWidgetItem());
//            table2->setItem(rowcount,3,new QTableWidgetItem("斑块相似度"));
//            table2->setItem(rowcount,4,new QTableWidgetItem(QString::number(deg94)));
//            table2->setSpan(rowcount-4+1,2,4,1);
//            table2->setSpan(rowcount-9*4+1,1,9*4,1);
//        }
//        if(rowcount2!=0){
//            table2->setSpan(rowcount-rowcount2+1,0,rowcount2,1);
//        }
//    }
}

void ResultWidget::generatereport(){
    //弹出对话框，选择内容，版式，文档格式
//    ReportInfo* ri = new ReportInfo();
//    FormatSelectionDialog* fsd = new FormatSelectionDialog(this,ri);
//    fsd->exec();
//    ContentSelectionDialog* csd = nullptr;
//    if(ri->format == 1||ri->format == 2){
//        csd = new ContentSelectionDialog(this,ri);
//        csd->exec();
//        if(ri->isContentSelected){
//            QString file = QFileDialog::getOpenFileName(this,tr("选择保存文件"),"","*.doc",0);
//            if(!file.isNull()){
//                QFile f(file);
//                if(!f.exists()){
//                    QFile::copy("./image/word.doc",file);
//                }
//                //调用生成报告的代码
//                WaitingDialog* wd = new WaitingDialog(this);
//                wd->setLText("正在生成评估报告，需要几分钟的时间，请耐心等候......");
//                wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
//                wd->setFixedWidth(QApplication::desktop()->width()/2);
//                wd->setFixedHeight(QApplication::desktop()->height()/10);
//                wd->setModal(true);
//                wd->show();
//                wd->l->repaint();
//                QEventLoop loop;//定义一个新的事件循环
//                QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//                loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
//                this->data->saveData();
//                ReportUtils ru = ReportUtils();
//                ru.generateWord(file,this->data,ri);
//                wd->close();
//                delete wd;
//            }
//        }
//        else{

//        }
//    }
//    else {

//    }
//    delete ri;
    //delete fsd;
    //delete csd;
}
