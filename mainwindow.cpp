#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QDir>
#include <QList>
#include <fstream>
#include <QStringList>
#include <QFile>
#include <QDesktopWidget>
#include <QTextStream>
#include <QTimer>
#include <QEventLoop>
#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/photo.hpp>
#include <opencv2/cvconfig.h>
#include <opencv2/imgproc.hpp>
#include "utils.h"
#include "Word/reportutils.h"
#include "waitingdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    projectfile="";
    dm = new DataModel();
    dm->clearTemp();
    QWidget* widget = new QWidget(this);
    lay = new QGridLayout(widget);
    this->addMyMenu();
    this->addMyToolBar();
    this->splitter1 = new QSplitter(Qt::Horizontal,this);
    this->splitter2 = new QSplitter(Qt::Vertical,this);

    this->iw1 = new ImageWidget(this,0);
    this->iw2 = new ImageWidget(this,1);
    //QString matfile = "./image/timg.bmp";
    //cv::Mat mat = cv::imread(matfile.toStdString());

    //iw1->setMat(mat);
    //iw2->setMat(mat);
    iw1->setData(dm);
    iw2->setData(dm);
    iw1->setAnother(iw2);
    iw2->setAnother(iw1);

    this->rw = new ResultWidget(this);
    rw->setData(dm);
    this->tw = new TreeWidget(this);
    tw->setDataModel(dm);
    tw->setImageWidget1(iw1);
    tw->setImageWidget2(iw2);
    iw1->setResultWidget(rw);
    iw2->setResultWidget(rw);
    this->splitter2->addWidget(iw1);
    this->splitter2->addWidget(iw2);
    this->splitter2->setOpaqueResize(true);
    this->splitter2->setStretchFactor(0,1);
    this->splitter2->setStretchFactor(1,1);
    this->splitter2->setHandleWidth(1);
    this->splitter1->addWidget(tw);
    this->splitter1->addWidget(splitter2);
    this->splitter1->addWidget(rw);
    this->splitter1->setOpaqueResize(true);
    this->splitter1->setStretchFactor(0,1);
    this->splitter1->setStretchFactor(1,2);
    this->splitter1->setStretchFactor(2,1);
    this->splitter1->setHandleWidth(1);

    lay->addWidget(menubar,0,0);
    lay->addWidget(toolbar,1,0);
    lay->addWidget(splitter1,2,0);
//    lay->setRowStretch(0,1);
    lay->setRowStretch(1,1);
    lay->setRowStretch(2,18);

    widget->setLayout(lay);
    this->setCentralWidget(widget);

    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("目标伪装效果评估软件");
    this->show();
}

MainWindow::~MainWindow(){
    dm->emptyData();
    delete dm;
}

void MainWindow::addMyMenu(){
    menubar = new QMenuBar(this);

    filemenu = new QMenu("项目");
    toolmenu = new QMenu("工具");
    helpmenu = new QMenu("帮助");

    newproject = new QAction("新建",this);
    connect(newproject,SIGNAL(triggered()),this,SLOT(newproject_Clicked()));
    filemenu->addAction(newproject);

    openproject = new QMenu("打开");
    openfromfile = new QAction("从文件打开",this);
    connect(openfromfile,SIGNAL(triggered()),this,SLOT(openfromfile_Clicked()));
    openproject->addAction(openfromfile);
    openfromdb = new QAction("从数据库打开",this);
    connect(openfromdb,SIGNAL(triggered()),this,SLOT(openfromdb_Clicked()));
    openproject->addAction(openfromdb);

    filemenu->addMenu(openproject);

    saveproject = new QAction("保存",this);
    connect(saveproject,SIGNAL(triggered()),this,SLOT(saveproject_Clicked()));
    saveasproject = new QAction("另存为",this);
    connect(saveasproject,SIGNAL(triggered()),this,SLOT(saveasproject_Clicked()));
//    closeproject = new QAction("关闭",this);
//    connect(closeproject,SIGNAL(triggered()),this,SLOT(closeproject_Clicked()));
    exitApp = new QAction("退出",this);
    connect(exitApp,SIGNAL(triggered()),this,SLOT(exitApp_Clicked()));

    filemenu->addAction(saveproject);
    filemenu->addAction(saveasproject);
//    filemenu->addAction(closeproject);
    filemenu->addAction(exitApp);

    dboperation = new QAction("数据库管理",this);
    connect(dboperation,SIGNAL(triggered()),this,SLOT(dboperation_Clicked()));
    toolmenu->addAction(dboperation);
    reportgeneration = new QAction("生成报告",this);
    connect(reportgeneration,SIGNAL(triggered()),this,SLOT(reportgeneration_Clicked()));
    toolmenu->addAction(reportgeneration);

    about = new QAction("关于",this);
    connect(about,SIGNAL(triggered()),this,SLOT(about_Clicked()));
    helpmenu->addAction(about);

    menubar->addMenu(filemenu);
    menubar->addMenu(toolmenu);
    menubar->addMenu(helpmenu);
}

void MainWindow::addMyToolBar(){
    toolbar = addToolBar("DM");
    pbNewproject = new QToolButton(this);
    pbNewproject->setText("新建");
    connect(pbNewproject, SIGNAL(clicked()), this, SLOT(newproject_Clicked()));
    pbOpenfromfile = new QToolButton(this);
    pbOpenfromfile->setText("从文件打开");
    connect(pbOpenfromfile, SIGNAL(clicked()), this, SLOT(openfromfile_Clicked()));
    pbOpenfromdb = new QToolButton(this);
    pbOpenfromdb->setText("从数据库打开");
    connect(pbOpenfromdb, SIGNAL(clicked()), this, SLOT(openfromdb_Clicked()));
    pbSaveproject = new QToolButton(this);
    pbSaveproject->setText("保存");
    connect(pbSaveproject, SIGNAL(clicked()), this, SLOT(saveproject_Clicked()));
    pbDBOperate = new QToolButton(this);
    pbDBOperate->setText("数据库管理");
    connect(pbDBOperate, SIGNAL(clicked()), this, SLOT(dboperation_Clicked()));
    pbReportgenerate = new QToolButton(this);
    pbReportgenerate->setText("生成报告");
    connect(pbReportgenerate, SIGNAL(clicked()), this, SLOT(reportgeneration_Clicked()));

    toolbar->addWidget(pbNewproject);
    toolbar->addWidget(pbOpenfromfile);
    toolbar->addWidget(pbOpenfromdb);
    toolbar->addWidget(pbSaveproject);
    toolbar->addSeparator();
    toolbar->addWidget(pbDBOperate);
    toolbar->addSeparator();
    toolbar->addWidget(pbReportgenerate);
}

void MainWindow::newproject_Clicked(){
    //QMessageBox::information(this,tr("新建工程"),tr("新建工程。继续努力。"));
    if(this->dm->isChanged){
        QMessageBox::StandardButton rb = QMessageBox::question(this, "保存提示", "当前项目内容已修改，是否需要保存？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            this->saveproject_Clicked();
        }
    }
    if(dm!=nullptr){
        dm->emptyData();
    }
    this->iw1->setMat();
    this->iw2->setMat();
    this->rw->setMat1(cv::Mat(),nullptr);
    this->rw->setMat2(cv::Mat(),nullptr);
    dm->clearTemp();
    this->tw->setDataModel(dm);
    this->iw1->setData(dm);
    this->iw2->setData(dm);
    this->rw->setData(dm);
    projectfile = "";
    this->dm->isChanged = false;
}

void MainWindow::openfromfile_Clicked(){
    //QMessageBox::information(this,tr("打开工程"),tr("从文件打开工程。继续努力。"));
    if(this->dm->isChanged){
        QMessageBox::StandardButton rb = QMessageBox::question(this, "保存提示", "当前项目内容已修改，是否需要保存？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            this->saveproject_Clicked();
        }
    }

    QString file = QFileDialog::getOpenFileName(this,tr("打开项目"),"default.cas","*.cas",0);
    if(!file.isNull()){
        QStringList as;
        this->projectfile = file;
        QFile ftfile(projectfile);
        ftfile.open(QIODevice::ReadOnly);
        if (ftfile.isOpen()){
            QString strtemp;
            QTextStream fttextStream(&ftfile);
            while(!fttextStream.atEnd()){
                strtemp = fttextStream.readLine();
                as<<strtemp;
            }
        }
        ftfile.close();
        if(as.size()==0){

        }
        else{
            WaitingDialog* wd = new WaitingDialog(this);
            wd->setLText("正在打开项目，需要若干秒的时间，请耐心等候......");
            wd->setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog);
            wd->setFixedWidth(QApplication::desktop()->width()/2);
            wd->setFixedHeight(QApplication::desktop()->height()/10);
            wd->setModal(true);
            wd->show();
            wd->l->repaint();
            QEventLoop loop;//定义一个新的事件循环
            QTimer::singleShot(100, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
            loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
            if(dm!=nullptr){
                dm->emptyData();
            }
            this->iw1->setMat();
            this->iw2->setMat();
            this->rw->setMat1(cv::Mat(),nullptr);
            this->rw->setMat2(cv::Mat(),nullptr);
            dm->clearTemp();
            this->tw->setDataModel(dm);
            this->iw1->setData(dm);
            this->iw2->setData(dm);
            this->rw->setData(dm);
            wd->close();
            delete wd;
            this->dm->isChanged = false;
        }
    }
}

void MainWindow::saveproject_Clicked(){
    //QMessageBox::information(this,tr("保存工程"),tr("保存工程。继续努力。"));
    if(this->projectfile=="")
        this->saveasproject_Clicked();
    else{
        //保存到数据库
//        this->dm->saveToDB();
//        //保存到文件
//        QList<Assess*> as = this->dm->getAssesses();
//        ofstream fout;
//        fout.open(this->projectfile.toLocal8Bit(),ios::out);
//        for(int i=0;i<as.size();i++){
//            fout<<as[i]->DataID.toStdString()<<endl;
//        }
//        fout.close();
        this->dm->isChanged = false;
        QMessageBox::information(this,tr("保存成功"),tr("项目保存成功！"));
    }
}

void MainWindow::saveasproject_Clicked(){
    //QMessageBox::information(this,tr("另存为工程"),tr("另存为工程。继续努力。"));
    QString file = QFileDialog::getSaveFileName(this,tr("保存项目"),"defalut.cas","*.cas",0);
    if(!file.isNull()){
        this->projectfile = file;
        this->saveproject_Clicked();
    }
}

//void MainWindow::closeproject_Clicked(){
//    QMessageBox::information(this,tr("关闭工程"),tr("关闭工程。继续努力。"));


//}

void MainWindow::about_Clicked(){
    QMessageBox::about(this,tr("关于本软件"),tr("目标伪装效果评估软件，由北京工业大学信息学部计算机学院研制。"));
}

void MainWindow::exitApp_Clicked(){
//    if(this->dm->isChanged){
//        QMessageBox::StandardButton rb = QMessageBox::question(this, "保存提示", "当前项目内容已修改，是否需要保存？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//        if(rb == QMessageBox::Yes){
//            this->saveproject_Clicked();
//        }
//    }
//    this->dm->clearTemp();
    QApplication::closeAllWindows();
}

void MainWindow::reportgeneration_Clicked(){
    //QMessageBox::information(this,tr("生成报告"),tr("生成报告。继续努力。"));
//    ReportInfo* ri = new ReportInfo();
//    FormatSelectionDialog* fsd = new FormatSelectionDialog(this,ri);
//    fsd->exec();
//    ContentSelectionDialog* csd = nullptr;
//    if(ri->format == 1||ri->format == 2){
//        csd = new ContentSelectionDialog(this,ri);
//        csd->exec();
//        if(ri->isContentSelected){
//            QString file = QFileDialog::getSaveFileName(this,tr("选择保存文件"),"","*.doc",0);
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
//                this->dm->saveData();
//                ReportUtils ru = ReportUtils();
//                ru.generateWord(file,this->dm,ri);
//                wd->close();
//                //delete wd;
//            }
//        }
//        else{

//        }
//    }
//    else {

//    }
    //delete ri;
    //delete fsd;
    //delete csd;
}


void MainWindow::mouseMoveEvent(QMouseEvent *e){
    e->ignore();
}

void MainWindow::closeEvent(QCloseEvent*event){
    if(this->dm->isChanged){
        QMessageBox::StandardButton rb = QMessageBox::question(this, "保存提示", "当前项目内容已修改，是否需要保存？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            this->saveproject_Clicked();
        }
    }
    this->dm->clearTemp();
    event->accept();
}
