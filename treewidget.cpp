#include "treewidget.h"

#include <QGridLayout>
#include <QDateTime>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
//#include "datagui/assessadddialog.h"
//#include "datagui/assessesadddialog.h"

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent)
{
    this->assesscount = 1;
    this->tree = new QTreeWidget(this);
    tree->setColumnCount(1);
    tree->setHeaderLabel("评估导航");
    QHeaderView *head=tree->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    tree->resize(this->width(), this->height());
    //tree->header().setResizeMode(QHeaderView::ResizeToContents);
    //qsa = new QScrollArea(this);
    //qsa->setWidget(tree);
    //QGridLayout* lay = new QGridLayout(this);
    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(tree);
    this->setLayout(lay);

    Add_Assess = new QAction(tr("添加评估"), this);
    Add_OpticesAssess = new QAction(tr("添加光学评估"),this);
    Add_InfraredAssess = new QAction(tr("添加红外评估"), this);
    Add_SARAssess = new QAction(tr("添加SAR评估"), this);
    Delete = new QAction(tr("删除"), this);
    To_IW1 = new QAction(tr("到显示区1"),this);
    To_IW2 = new QAction(tr("到显示区2"),this);
    Load_Image = new QAction(tr("载入图像"), this);
    connect(Add_Assess, SIGNAL(triggered()), this, SLOT(addAssess()));
    connect(Add_OpticesAssess, SIGNAL(triggered()), this, SLOT(addOpticesAssess()));
    connect(Add_InfraredAssess, SIGNAL(triggered()), this, SLOT(addInfraredAssess()));
    connect(Add_SARAssess, SIGNAL(triggered()), this, SLOT(addSARAssess()));
    connect(Delete, SIGNAL(triggered()), this, SLOT(deleteItem()));
    connect(To_IW1, SIGNAL(triggered()), this, SLOT(toIW1()));
    connect(To_IW2, SIGNAL(triggered()), this, SLOT(toIW2()));
    connect(Load_Image, SIGNAL(triggered()), this, SLOT(loadImage()));
}

TreeWidget::~TreeWidget(){
//    delete tree;
//    //delete qsa;
//    delete Add_Assess;
//    delete Add_OpticesAssess;
//    delete Add_InfraredAssess;
//    delete Add_SARAssess;
//    delete Delete;
//    delete To_IW1;
//    delete To_IW2;
//    delete Load_Image;
}

void TreeWidget::resizeEvent(QResizeEvent *e){
    tree->resize(this->width(),this->height());
}

void TreeWidget::addAssess(){
    //int size = tree->topLevelItemCount();
    //qDebug()<<size;
//    Assess* assess = data->createAssess();
//    AssessAddDialog* dialog = new AssessAddDialog(this,assess);
//    dialog->exec();
//    if(assess->AName==""){
//        data->removeAssess(assess->DataID);
//    }
//    else{
//        this->data->isChanged = true;
//        assess->Time = QDateTime::currentDateTime();
//        assess->Intro = "评估创建于"+assess->Time.toString();
//        assess->OpticesID="";
//        assess->InfraredID="";
//        assess->SARID="";
//        //assess->AName="评估"+QString::number(this->assesscount);
//        QTreeWidgetItem* assessItem = new QTreeWidgetItem(tree,QStringList(assess->AName),0);
//        this->assesscount++;
//        assessItem->setData(0,1,assess->DataID);
//        assessItem->setData(1,1,0);
//        tree->addTopLevelItem(assessItem);
//        tree->expandAll();
//    }
}

void TreeWidget::addOpticesAssess(){
//    QTreeWidgetItem* citem = tree->currentItem();
//    QString id = citem->data(0,1).toString();
//    Assess* assess = data->getAssess(id);
//    OpticesAssess* opticesAssess = data->createOpticesAssess();
//    AssessesAddDialog* dialog = new AssessesAddDialog(this,opticesAssess);
//    dialog->exec();
//    if(opticesAssess->isCanceled){
//        data->removeOpticesAssess(opticesAssess->DataID);
//    }
//    else{
//        this->data->isChanged = true;
//        assess->OpticesID = opticesAssess->DataID;
//        if(opticesAssess->AssID!=""){
//            this->data->createCamouflage(opticesAssess->AssID);
//            Camouflage* cam = this->data->getCamouflage(opticesAssess->AssID);
//            cam->selectFromDB(opticesAssess->AssID);
//            if(cam->CamMaterialID!=""){
//                this->data->createCamMaterial(cam->CamMaterialID);
//                CamMaterial* camma = this->data->getCamMaterial(cam->CamMaterialID);
//                camma->selectFromDB(cam->CamMaterialID);
//            }
//            if(cam->CamMethodID!=""){
//                this->data->createCamMethod(cam->CamMethodID);
//                CamMethod* camme = this->data->getCamMethod(cam->CamMethodID);
//                camme->selectFromDB(cam->CamMethodID);
//            }
//        }
//        if(opticesAssess->ExID!=""){
//            this->data->createExperiment(opticesAssess->ExID);
//            Experiment* ex = this->data->getExperiment(opticesAssess->ExID);
//            ex->selectFromDB(opticesAssess->ExID);
//            if(ex->PID!=""){
//                this->data->createPeople(ex->PID);
//                People* p = this->data->getPeople(ex->PID);
//                p->selectFromDB(ex->PID);
//            }
//        }
//        if(opticesAssess->PID!=""){
//            this->data->createPeople(opticesAssess->PID);
//            People* p = this->data->getPeople(opticesAssess->PID);
//            p->selectFromDB(opticesAssess->PID);
//        }
//        if(opticesAssess->EqID!=""){
//            this->data->createEquipment(opticesAssess->EqID);
//            Equipment* eq = this->data->getEquipment(opticesAssess->EqID);
//            eq->selectFromDB(opticesAssess->EqID);
//        }
//        if(opticesAssess->EnID!=""){
//            this->data->createEnvironment(opticesAssess->EnID);
//            Environment* en = this->data->getEnvironment(opticesAssess->EnID);
//            en->selectFromDB(opticesAssess->EnID);
//        }
//        if(opticesAssess->ObjID!=""){
//            this->data->createObject(opticesAssess->ObjID);
//            Object* obj = this->data->getObject(opticesAssess->ObjID);
//            obj->selectFromDB(opticesAssess->ObjID);
//        }
//        if(opticesAssess->FObjID!=""){
//            this->data->createFObject(opticesAssess->FObjID);
//            FObject* fobj = this->data->getFObject(opticesAssess->FObjID);
//            fobj->selectFromDB(opticesAssess->FObjID);
//        }
//        QTreeWidgetItem* opticesAssessItem = new QTreeWidgetItem(citem,QStringList(QString("光学评估")),1);
//        opticesAssessItem->setData(0,1,opticesAssess->DataID);
//        opticesAssessItem->setData(1,1,1);
//        citem->addChild(opticesAssessItem);
//        //光学评估
//        //Obj
//        QTreeWidgetItem* objOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("真目标图像")),10);
//        objOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        objOpticesAssessItem->setData(1,1,10);
//        opticesAssessItem->addChild(objOpticesAssessItem);
//        //ObjBack
//        QTreeWidgetItem* objbackOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含真目标图像")),11);
//        objbackOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        objbackOpticesAssessItem->setData(1,1,11);
//        opticesAssessItem->addChild(objbackOpticesAssessItem);
//        //FObj
//        QTreeWidgetItem* fobjOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("示假目标图像")),12);
//        fobjOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        fobjOpticesAssessItem->setData(1,1,12);
//        opticesAssessItem->addChild(fobjOpticesAssessItem);
//        //FObjBack
//        QTreeWidgetItem* fobjbackOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含示假目标图像")),13);
//        fobjbackOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        fobjbackOpticesAssessItem->setData(1,1,13);
//        opticesAssessItem->addChild(fobjbackOpticesAssessItem);
//        //BObj
//        QTreeWidgetItem* bobjOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("目标背景图像")),14);
//        bobjOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        bobjOpticesAssessItem->setData(1,1,14);
//        opticesAssessItem->addChild(bobjOpticesAssessItem);
//        //Back
//        QTreeWidgetItem* backOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("背景图像")),15);
//        backOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        backOpticesAssessItem->setData(1,1,15);
//        opticesAssessItem->addChild(backOpticesAssessItem);
//        //Fill1
//        QTreeWidgetItem* fill1OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("真目标回填图像")),16);
//        fill1OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        fill1OpticesAssessItem->setData(1,1,16);
//        opticesAssessItem->addChild(fill1OpticesAssessItem);
//        //FillBack1
//        QTreeWidgetItem* fillback1OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含真目标回填图像")),17);
//        fillback1OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        fillback1OpticesAssessItem->setData(1,1,17);
//        opticesAssessItem->addChild(fillback1OpticesAssessItem);
//        //Fill2
//        QTreeWidgetItem* fill2OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("示假目标回填图像")),18);
//        fill2OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        fill2OpticesAssessItem->setData(1,1,18);
//        opticesAssessItem->addChild(fill2OpticesAssessItem);
//        //FillBack2
//        QTreeWidgetItem* fillback2OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含示假目标回填图像")),19);
//        fillback2OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//        fillback2OpticesAssessItem->setData(1,1,19);
//        opticesAssessItem->addChild(fillback2OpticesAssessItem);
//        //设置默认值
//        opticesAssess->Intro="光学评估创建于"+QDateTime::currentDateTime().toString();
//        //弹出对话框设置光学评估相关属性

//        tree->expandAll();
//    }
}

void TreeWidget::addInfraredAssess(){
//    QTreeWidgetItem* citem = tree->currentItem();
//    QString id = citem->data(0,1).toString();
//    Assess* assess = data->getAssess(id);
//    InfraredAssess* infraredAssess = data->createInfraredAssess();
//    AssessesAddDialog* dialog = new AssessesAddDialog(this,infraredAssess);
//    dialog->exec();
//    if(infraredAssess->isCanceled){
//        data->removeOpticesAssess(infraredAssess->DataID);
//    }
//    else{
//        this->data->isChanged = true;
//        assess->InfraredID = infraredAssess->DataID;
//        if(infraredAssess->AssID!=""){
//            this->data->createCamouflage(infraredAssess->AssID);
//            Camouflage* cam = this->data->getCamouflage(infraredAssess->AssID);
//            cam->selectFromDB(infraredAssess->AssID);
//            if(cam->CamMaterialID!=""){
//                this->data->createCamMaterial(cam->CamMaterialID);
//                CamMaterial* camma = this->data->getCamMaterial(cam->CamMaterialID);
//                camma->selectFromDB(cam->CamMaterialID);
//            }
//            if(cam->CamMethodID!=""){
//                this->data->createCamMethod(cam->CamMethodID);
//                CamMethod* camme = this->data->getCamMethod(cam->CamMethodID);
//                camme->selectFromDB(cam->CamMethodID);
//            }
//        }
//        if(infraredAssess->ExID!=""){
//            this->data->createExperiment(infraredAssess->ExID);
//            Experiment* ex = this->data->getExperiment(infraredAssess->ExID);
//            ex->selectFromDB(infraredAssess->ExID);
//            if(ex->PID!=""){
//                this->data->createPeople(ex->PID);
//                People* p = this->data->getPeople(ex->PID);
//                p->selectFromDB(ex->PID);
//            }
//        }
//        if(infraredAssess->PID!=""){
//            this->data->createPeople(infraredAssess->PID);
//            People* p = this->data->getPeople(infraredAssess->PID);
//            p->selectFromDB(infraredAssess->PID);
//        }
//        if(infraredAssess->EqID!=""){
//            this->data->createEquipment(infraredAssess->EqID);
//            Equipment* eq = this->data->getEquipment(infraredAssess->EqID);
//            eq->selectFromDB(infraredAssess->EqID);
//        }
//        if(infraredAssess->EnID!=""){
//            this->data->createEnvironment(infraredAssess->EnID);
//            Environment* en = this->data->getEnvironment(infraredAssess->EnID);
//            en->selectFromDB(infraredAssess->EnID);
//        }
//        if(infraredAssess->ObjID!=""){
//            this->data->createObject(infraredAssess->ObjID);
//            Object* obj = this->data->getObject(infraredAssess->ObjID);
//            obj->selectFromDB(infraredAssess->ObjID);
//        }
//        if(infraredAssess->FObjID!=""){
//            this->data->createFObject(infraredAssess->FObjID);
//            FObject* fobj = this->data->getFObject(infraredAssess->FObjID);
//            fobj->selectFromDB(infraredAssess->FObjID);
//        }
//        QTreeWidgetItem* infraredAssessItem = new QTreeWidgetItem(citem,QStringList(QString("红外评估")),2);
//        infraredAssessItem->setData(0,1,infraredAssess->DataID);
//        infraredAssessItem->setData(1,1,2);
//        citem->addChild(infraredAssessItem);
//        //红外评估
//        //Obj
//        QTreeWidgetItem* objInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("真目标图像")),20);
//        objInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        objInfraredAssessItem->setData(1,1,20);
//        infraredAssessItem->addChild(objInfraredAssessItem);
//        //ObjBack
//        QTreeWidgetItem* objbackInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含真目标图像")),21);
//        objbackInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        objbackInfraredAssessItem->setData(1,1,21);
//        infraredAssessItem->addChild(objbackInfraredAssessItem);
//        //FObj
//        QTreeWidgetItem* fobjInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("示假目标图像")),22);
//        fobjInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        fobjInfraredAssessItem->setData(1,1,22);
//        infraredAssessItem->addChild(fobjInfraredAssessItem);
//        //FObjBack
//        QTreeWidgetItem* fobjbackInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含示假目标图像")),23);
//        fobjbackInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        fobjbackInfraredAssessItem->setData(1,1,23);
//        infraredAssessItem->addChild(fobjbackInfraredAssessItem);
//        //BObj
//        QTreeWidgetItem* bobjInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("目标背景图像")),24);
//        bobjInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        bobjInfraredAssessItem->setData(1,1,24);
//        infraredAssessItem->addChild(bobjInfraredAssessItem);
//        //Back
//        QTreeWidgetItem* backInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("背景图像")),25);
//        backInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        backInfraredAssessItem->setData(1,1,25);
//        infraredAssessItem->addChild(backInfraredAssessItem);
//        //Fill1
//        QTreeWidgetItem* fill1InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("真目标回填图像")),26);
//        fill1InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        fill1InfraredAssessItem->setData(1,1,26);
//        infraredAssessItem->addChild(fill1InfraredAssessItem);
//        //FillBack1
//        QTreeWidgetItem* fillback1InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含真目标回填图像")),27);
//        fillback1InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        fillback1InfraredAssessItem->setData(1,1,27);
//        infraredAssessItem->addChild(fillback1InfraredAssessItem);
//        //Fill2
//        QTreeWidgetItem* fill2InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("示假目标回填图像")),28);
//        fill2InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        fill2InfraredAssessItem->setData(1,1,28);
//        infraredAssessItem->addChild(fill2InfraredAssessItem);
//        //FillBack2
//        QTreeWidgetItem* fillback2InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含示假目标回填图像")),29);
//        fillback2InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//        fillback2InfraredAssessItem->setData(1,1,29);
//        infraredAssessItem->addChild(fillback2InfraredAssessItem);
//        //设置默认值

//        infraredAssess->Intro="红外评估创建于"+QDateTime::currentDateTime().toString();
//        //弹出对话框设置红外评估相关属性

//        tree->expandAll();
//    }
}

void TreeWidget::addSARAssess(){
//    QTreeWidgetItem* citem = tree->currentItem();
//    QString id = citem->data(0,1).toString();
//    Assess* assess = data->getAssess(id);
//    SARAssess* sarAssess = data->createSARAssess();
//    AssessesAddDialog* dialog = new AssessesAddDialog(this,sarAssess);
//    dialog->exec();
//    if(sarAssess->isCanceled){
//        data->removeOpticesAssess(sarAssess->DataID);
//    }
//    else{
//        this->data->isChanged = true;
//        assess->SARID = sarAssess->DataID;
//        if(sarAssess->AssID!=""){
//            this->data->createCamouflage(sarAssess->AssID);
//            Camouflage* cam = this->data->getCamouflage(sarAssess->AssID);
//            cam->selectFromDB(sarAssess->AssID);
//            if(cam->CamMaterialID!=""){
//                this->data->createCamMaterial(cam->CamMaterialID);
//                CamMaterial* camma = this->data->getCamMaterial(cam->CamMaterialID);
//                camma->selectFromDB(cam->CamMaterialID);
//            }
//            if(cam->CamMethodID!=""){
//                this->data->createCamMethod(cam->CamMethodID);
//                CamMethod* camme = this->data->getCamMethod(cam->CamMethodID);
//                camme->selectFromDB(cam->CamMethodID);
//            }
//        }
//        if(sarAssess->ExID!=""){
//            this->data->createExperiment(sarAssess->ExID);
//            Experiment* ex = this->data->getExperiment(sarAssess->ExID);
//            ex->selectFromDB(sarAssess->ExID);
//            if(ex->PID!=""){
//                this->data->createPeople(ex->PID);
//                People* p = this->data->getPeople(ex->PID);
//                p->selectFromDB(ex->PID);
//            }
//        }
//        if(sarAssess->PID!=""){
//            this->data->createPeople(sarAssess->PID);
//            People* p = this->data->getPeople(sarAssess->PID);
//            p->selectFromDB(sarAssess->PID);
//        }
//        if(sarAssess->EqID!=""){
//            this->data->createEquipment(sarAssess->EqID);
//            Equipment* eq = this->data->getEquipment(sarAssess->EqID);
//            eq->selectFromDB(sarAssess->EqID);
//        }
//        if(sarAssess->EnID!=""){
//            this->data->createEnvironment(sarAssess->EnID);
//            Environment* en = this->data->getEnvironment(sarAssess->EnID);
//            en->selectFromDB(sarAssess->EnID);
//        }
//        if(sarAssess->ObjID!=""){
//            this->data->createObject(sarAssess->ObjID);
//            Object* obj = this->data->getObject(sarAssess->ObjID);
//            obj->selectFromDB(sarAssess->ObjID);
//        }
//        if(sarAssess->FObjID!=""){
//            this->data->createFObject(sarAssess->FObjID);
//            FObject* fobj = this->data->getFObject(sarAssess->FObjID);
//            fobj->selectFromDB(sarAssess->FObjID);
//        }
//        QTreeWidgetItem* sarAssessItem = new QTreeWidgetItem(citem,QStringList(QString("SAR评估")),3);
//        sarAssessItem->setData(0,1,sarAssess->DataID);
//        sarAssessItem->setData(1,1,3);
//        citem->addChild(sarAssessItem);
//        //第三层
//        //SAR评估
//        //Obj
//        QTreeWidgetItem* objSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("真目标图像")),30);
//        objSARAssessItem->setData(0,1,sarAssess->DataID);
//        objSARAssessItem->setData(1,1,30);
//        sarAssessItem->addChild(objSARAssessItem);
//        //ObjBack
//        QTreeWidgetItem* objbackSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含真目标图像")),31);
//        objbackSARAssessItem->setData(0,1,sarAssess->DataID);
//        objbackSARAssessItem->setData(1,1,31);
//        sarAssessItem->addChild(objbackSARAssessItem);
//        //FObj
//        QTreeWidgetItem* fobjSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("示假目标图像")),32);
//        fobjSARAssessItem->setData(0,1,sarAssess->DataID);
//        fobjSARAssessItem->setData(1,1,32);
//        sarAssessItem->addChild(fobjSARAssessItem);
//        //FObjBack
//        QTreeWidgetItem* fobjbackSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含示假目标图像")),33);
//        fobjbackSARAssessItem->setData(0,1,sarAssess->DataID);
//        fobjbackSARAssessItem->setData(1,1,33);
//        sarAssessItem->addChild(fobjbackSARAssessItem);
//        //BObj
//        QTreeWidgetItem* bobjSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("目标背景图像")),34);
//        bobjSARAssessItem->setData(0,1,sarAssess->DataID);
//        bobjSARAssessItem->setData(1,1,34);
//        sarAssessItem->addChild(bobjSARAssessItem);
//        //Back
//        QTreeWidgetItem* backSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("背景图像")),35);
//        backSARAssessItem->setData(0,1,sarAssess->DataID);
//        backSARAssessItem->setData(1,1,35);
//        sarAssessItem->addChild(backSARAssessItem);
//        //Fill1
//        QTreeWidgetItem* fill1SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("真目标回填图像")),36);
//        fill1SARAssessItem->setData(0,1,sarAssess->DataID);
//        fill1SARAssessItem->setData(1,1,36);
//        sarAssessItem->addChild(fill1SARAssessItem);
//        //FillBack1
//        QTreeWidgetItem* fillback1SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含真目标回填图像")),37);
//        fillback1SARAssessItem->setData(0,1,sarAssess->DataID);
//        fillback1SARAssessItem->setData(1,1,37);
//        sarAssessItem->addChild(fillback1SARAssessItem);
//        //Fill2
//        QTreeWidgetItem* fill2SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("示假目标回填图像")),38);
//        fill2SARAssessItem->setData(0,1,sarAssess->DataID);
//        fill2SARAssessItem->setData(1,1,38);
//        sarAssessItem->addChild(fill2SARAssessItem);
//        //FillBack2
//        QTreeWidgetItem* fillback2SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含示假目标回填图像")),39);
//        fillback2SARAssessItem->setData(0,1,sarAssess->DataID);
//        fillback2SARAssessItem->setData(1,1,39);
//        sarAssessItem->addChild(fillback2SARAssessItem);
//        //设置默认值
//        sarAssess->Intro="SAR评估创建于"+QDateTime::currentDateTime().toString();
//        //弹出对话框设置SAR评估相关属性

//        tree->expandAll();
//    }
}

void TreeWidget::deleteItem(){
    QTreeWidgetItem* citem = tree->currentItem();
    if(citem!=NULL){
        QMessageBox::StandardButton rb = QMessageBox::question(this, "评估删除", "评估数据删除以后不可恢复，确定要删除吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::No){
            return;
        }
        int type = citem->type();
//        Assess* assess;
//        switch (type) {
//        case 0:
//            this->data->isChanged = true;
//            this->data->removeAssess(citem->data(0,1).toString());
//            tree->removeItemWidget(citem,0);
//            delete citem;
//            break;
//        case 1:
//            this->data->isChanged = true;
//            this->data->removeOpticesAssess(citem->data(0,1).toString());
//            assess = this->data->getAssess(citem->parent()->data(0,1).toString());
//            assess->OpticesID = "";
//            citem->parent()->removeChild(citem);
//            delete citem;
//            break;
//        case 2:
//            this->data->isChanged = true;
//            this->data->removeInfraredAssess(citem->data(0,1).toString());
//            assess = this->data->getAssess(citem->parent()->data(0,1).toString());
//            assess->InfraredID = "";
//            citem->parent()->removeChild(citem);
//            delete citem;
//            break;
//        case 3:
//            this->data->isChanged = true;
//            this->data->removeSARAssess(citem->data(0,1).toString());
//            assess = this->data->getAssess(citem->parent()->data(0,1).toString());
//            assess->SARID = "";
//            citem->parent()->removeChild(citem);
//            delete citem;
//            break;
//        default:
//            break;
//        }
    }
    tree->expandAll();
}

void TreeWidget::toIW1(){
//    QTreeWidgetItem* citem = tree->currentItem();
//    if(citem!=NULL){
//        int type = citem->type();
//        qDebug()<<type;
//        OpticesAssess* opticesAssess;
//        InfraredAssess* infraredAssess;
//        SARAssess* sarAssess;
//        switch (type) {
//        case 10:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 11:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            //qDebug()<<opticesAssess->DataID;
//            break;
//        case 12:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 13:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 14:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 15:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 16:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 17:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 18:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 19:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw1->setMat(opticesAssess,type);
//            break;
//        case 20:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 21:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 22:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 23:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 24:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 25:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 26:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 27:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 28:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 29:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw1->setMat(infraredAssess, type);
//            break;
//        case 30:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 31:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 32:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 33:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 34:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 35:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 36:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 37:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 38:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        case 39:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw1->setMat(sarAssess, type);
//            break;
//        default:
//            break;
//        }
//    }
}

void TreeWidget::toIW2(){
//    QTreeWidgetItem* citem = tree->currentItem();
//    if(citem!=NULL){
//        int type = citem->type();
//        OpticesAssess* opticesAssess;
//        InfraredAssess* infraredAssess;
//        SARAssess* sarAssess;
//        switch (type) {
//        case 10:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 11:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 12:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 13:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 14:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 15:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 16:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 17:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 18:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 19:
//            opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//            if(opticesAssess!=nullptr)
//                this->iw2->setMat(opticesAssess,type);
//            break;
//        case 20:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 21:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 22:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 23:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 24:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 25:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 26:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            this->iw2->setMat(infraredAssess, type);
//            break;
//        case 27:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 28:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 29:
//            infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//            if(infraredAssess!=nullptr)
//                this->iw2->setMat(infraredAssess, type);
//            break;
//        case 30:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 31:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 32:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 33:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 34:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 35:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 36:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 37:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 38:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        case 39:
//            sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//            if(sarAssess!=nullptr)
//                this->iw2->setMat(sarAssess, type);
//            break;
//        default:
//            break;
//        }
//    }
}

void TreeWidget::loadImage(){
//    QString file = QFileDialog::getOpenFileName(this,tr("载入图像"),"","*.*",0);
//    if(!file.isNull()){
//        QTreeWidgetItem* citem = tree->currentItem();
//        if(citem!=NULL){
//            this->data->isChanged = true;
//            int type = citem->type();
//            OpticesAssess* opticesAssess;
//            InfraredAssess* infraredAssess;
//            SARAssess* sarAssess;
//            switch (type) {
//            case 11:
//                opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//                opticesAssess->setObjBackFile(file);
//                this->toIW1();
//                break;
//            case 13:
//                opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//                opticesAssess->setFObjBackFile(file);
//                this->toIW2();
//                break;
//            case 15:
//                opticesAssess = this->data->getOpticesAssess(citem->data(0,1).toString());
//                opticesAssess->setBackFile(file);
//                this->toIW2();
//                break;
//            case 21:
//                infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//                infraredAssess->setObjBackFile(file);
//                this->toIW1();
//                break;
//            case 23:
//                infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//                infraredAssess->setFObjBackFile(file);
//                this->toIW2();
//                break;
//            case 25:
//                infraredAssess = this->data->getInfraredAssess(citem->data(0,1).toString());
//                infraredAssess->setBackFile(file);
//                this->toIW2();
//                break;
//            case 31:
//                sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//                sarAssess->setObjBackFile(file);
//                this->toIW1();
//                break;
//            case 33:
//                sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//                sarAssess->setFObjBackFile(file);
//                this->toIW2();
//                break;
//            case 35:
//                sarAssess = this->data->getSARAssess(citem->data(0,1).toString());
//                sarAssess->setBackFile(file);
//                this->toIW2();
//                break;
//            default:
//                break;
//            }
//        }
//    }
}

void TreeWidget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->setStyleSheet(QString::fromUtf8("border:0px"));
    menu->addAction(Add_Assess);
    QTreeWidgetItem* citem = tree->currentItem();
    if(citem!=NULL){
        int type = citem->type();
//        Assess* assess;
//        switch (type) {
//        case 0:
//            assess = this->data->getAssess(citem->data(0,1).toString());
//            if(assess->OpticesID==""){
//                menu->addAction(Add_OpticesAssess);
//            }
//            if(assess->InfraredID==""){
//                menu->addAction(Add_InfraredAssess);
//            }
//            if(assess->SARID==""){
//                menu->addAction(Add_SARAssess);
//            }
//            menu->addAction(Delete);
//            break;
//        case 1:
//            menu->addAction(Delete);
//            break;
//        case 2:
//            menu->addAction(Delete);
//            break;
//        case 3:
//            menu->addAction(Delete);
//            break;
//        case 11:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 13:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 15:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 21:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 23:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 25:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 31:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 33:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        case 35:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            menu->addSeparator();
//            menu->addAction(Load_Image);
//            break;
//        default:
//            menu->addSeparator();
//            menu->addAction(To_IW1);
//            menu->addAction(To_IW2);
//            break;
//        }
    }
    menu->exec(cur.pos()); //关联到光标
}

void TreeWidget::setDataModel(DataModel* data){
    this->data = data;
    this->treeInitial();
}

void TreeWidget::setImageWidget1(ImageWidget* iw1){
    this->iw1 = iw1;
}

void TreeWidget::setImageWidget2(ImageWidget* iw2){
    this->iw2 = iw2;
}

void TreeWidget::setResultWidget(ResultWidget* rw){
    this->rw = rw;
}

void TreeWidget::treeInitial(){
    tree->clear();
//    while(tree->topLevelItemCount())
//    {
//        QTreeWidgetItem* item = tree->takeTopLevelItem(0);
//        delete item;
//    }
//    QList<Assess*> assesses = data->getAssesses();
//    for(int i=0;i<assesses.size();i++){
//        Assess* assess = assesses[i];
//        //第一层，评估
//        QTreeWidgetItem* assessItem = new QTreeWidgetItem(tree,QStringList(assess->AName),0);
//        assessItem->setData(0,1,assess->DataID);
//        assessItem->setData(1,1,0);
//        tree->addTopLevelItem(assessItem);
//        //第二层
//        //光学评估
//        if(assess->OpticesID!=""){
//            OpticesAssess* opticesAssess = data->getOpticesAssess(assess->OpticesID);
//            QTreeWidgetItem* opticesAssessItem = new QTreeWidgetItem(assessItem,QStringList(QString("光学评估")),1);
//            opticesAssessItem->setData(0,1,opticesAssess->DataID);
//            opticesAssessItem->setData(1,1,1);
//            assessItem->addChild(opticesAssessItem);
//            //光学评估
//            //Obj
//            QTreeWidgetItem* objOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("真目标图像")),10);
//            objOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            objOpticesAssessItem->setData(1,1,10);
//            opticesAssessItem->addChild(objOpticesAssessItem);
//            //ObjBack
//            QTreeWidgetItem* objbackOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含真目标图像")),11);
//            objbackOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            objbackOpticesAssessItem->setData(1,1,11);
//            opticesAssessItem->addChild(objbackOpticesAssessItem);
//            //FObj
//            QTreeWidgetItem* fobjOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("示假目标图像")),12);
//            fobjOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            fobjOpticesAssessItem->setData(1,1,12);
//            opticesAssessItem->addChild(fobjOpticesAssessItem);
//            //FObjBack
//            QTreeWidgetItem* fobjbackOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含示假目标图像")),13);
//            fobjbackOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            fobjbackOpticesAssessItem->setData(1,1,13);
//            opticesAssessItem->addChild(fobjbackOpticesAssessItem);
//            //BObj
//            QTreeWidgetItem* bobjOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("目标背景图像")),14);
//            bobjOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            bobjOpticesAssessItem->setData(1,1,14);
//            opticesAssessItem->addChild(bobjOpticesAssessItem);
//            //Back
//            QTreeWidgetItem* backOpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("背景图像")),15);
//            backOpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            backOpticesAssessItem->setData(1,1,15);
//            opticesAssessItem->addChild(backOpticesAssessItem);
//            //Fill1
//            QTreeWidgetItem* fill1OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("真目标回填图像")),16);
//            fill1OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            fill1OpticesAssessItem->setData(1,1,16);
//            opticesAssessItem->addChild(fill1OpticesAssessItem);
//            //FillBack1
//            QTreeWidgetItem* fillback1OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含真目标回填图像")),17);
//            fillback1OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            fillback1OpticesAssessItem->setData(1,1,17);
//            opticesAssessItem->addChild(fillback1OpticesAssessItem);
//            //Fill2
//            QTreeWidgetItem* fill2OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("示假目标回填图像")),18);
//            fill2OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            fill2OpticesAssessItem->setData(1,1,18);
//            opticesAssessItem->addChild(fill2OpticesAssessItem);
//            //FillBack2
//            QTreeWidgetItem* fillback2OpticesAssessItem = new QTreeWidgetItem(opticesAssessItem,QStringList(QString("包含示假目标回填图像")),19);
//            fillback2OpticesAssessItem->setData(0,1,opticesAssess->DataID);
//            fillback2OpticesAssessItem->setData(1,1,19);
//            opticesAssessItem->addChild(fillback2OpticesAssessItem);
//        }
//        //红外评估
//        if(assess->InfraredID!=""){
//            InfraredAssess* infraredAssess = data->getInfraredAssess(assess->InfraredID);
//            QTreeWidgetItem* infraredAssessItem = new QTreeWidgetItem(assessItem,QStringList(QString("红外评估")),2);
//            infraredAssessItem->setData(0,1,infraredAssess->DataID);
//            infraredAssessItem->setData(1,1,2);
//            assessItem->addChild(infraredAssessItem);
//            //红外评估
//            //Obj
//            QTreeWidgetItem* objInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("真目标图像")),20);
//            objInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            objInfraredAssessItem->setData(1,1,20);
//            infraredAssessItem->addChild(objInfraredAssessItem);
//            //ObjBack
//            QTreeWidgetItem* objbackInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含真目标图像")),21);
//            objbackInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            objbackInfraredAssessItem->setData(1,1,21);
//            infraredAssessItem->addChild(objbackInfraredAssessItem);
//            //FObj
//            QTreeWidgetItem* fobjInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("示假目标图像")),22);
//            fobjInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            fobjInfraredAssessItem->setData(1,1,22);
//            infraredAssessItem->addChild(fobjInfraredAssessItem);
//            //FObjBack
//            QTreeWidgetItem* fobjbackInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含示假目标图像")),23);
//            fobjbackInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            fobjbackInfraredAssessItem->setData(1,1,23);
//            infraredAssessItem->addChild(fobjbackInfraredAssessItem);
//            //BObj
//            QTreeWidgetItem* bobjInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("目标背景图像")),24);
//            bobjInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            bobjInfraredAssessItem->setData(1,1,24);
//            infraredAssessItem->addChild(bobjInfraredAssessItem);
//            //Back
//            QTreeWidgetItem* backInfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("背景图像")),25);
//            backInfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            backInfraredAssessItem->setData(1,1,25);
//            infraredAssessItem->addChild(backInfraredAssessItem);
//            //Fill1
//            QTreeWidgetItem* fill1InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("真目标回填图像")),26);
//            fill1InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            fill1InfraredAssessItem->setData(1,1,26);
//            infraredAssessItem->addChild(fill1InfraredAssessItem);
//            //FillBack1
//            QTreeWidgetItem* fillback1InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含真目标回填图像")),27);
//            fillback1InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            fillback1InfraredAssessItem->setData(1,1,27);
//            infraredAssessItem->addChild(fillback1InfraredAssessItem);
//            //Fill2
//            QTreeWidgetItem* fill2InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("示假目标回填图像图像")),28);
//            fill2InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            fill2InfraredAssessItem->setData(1,1,28);
//            infraredAssessItem->addChild(fill2InfraredAssessItem);
//            //FillBack2
//            QTreeWidgetItem* fillback2InfraredAssessItem = new QTreeWidgetItem(infraredAssessItem,QStringList(QString("包含示假目标回填图像")),29);
//            fillback2InfraredAssessItem->setData(0,1,infraredAssess->DataID);
//            fillback2InfraredAssessItem->setData(1,1,29);
//            infraredAssessItem->addChild(fillback2InfraredAssessItem);
//        }
//        //SAR评估
//        if(assess->SARID!=""){
//            SARAssess* sarAssess = data->getSARAssess(assess->SARID);
//            QTreeWidgetItem* sarAssessItem = new QTreeWidgetItem(assessItem,QStringList(QString("SAR评估")),3);
//            sarAssessItem->setData(0,1,sarAssess->DataID);
//            sarAssessItem->setData(1,1,3);
//            assessItem->addChild(sarAssessItem);
//            //第三层
//            //SAR评估
//            //Obj
//            QTreeWidgetItem* objSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("真目标图像")),30);
//            objSARAssessItem->setData(0,1,sarAssess->DataID);
//            objSARAssessItem->setData(1,1,30);
//            sarAssessItem->addChild(objSARAssessItem);
//            //ObjBack
//            QTreeWidgetItem* objbackSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含真目标图像")),31);
//            objbackSARAssessItem->setData(0,1,sarAssess->DataID);
//            objbackSARAssessItem->setData(1,1,31);
//            sarAssessItem->addChild(objbackSARAssessItem);
//            //FObj
//            QTreeWidgetItem* fobjSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("示假目标图像")),32);
//            fobjSARAssessItem->setData(0,1,sarAssess->DataID);
//            fobjSARAssessItem->setData(1,1,32);
//            sarAssessItem->addChild(fobjSARAssessItem);
//            //FObjBack
//            QTreeWidgetItem* fobjbackSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含示假目标图像")),33);
//            fobjbackSARAssessItem->setData(0,1,sarAssess->DataID);
//            fobjbackSARAssessItem->setData(1,1,33);
//            sarAssessItem->addChild(fobjbackSARAssessItem);
//            //BObj
//            QTreeWidgetItem* bobjSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("目标背景图像")),34);
//            bobjSARAssessItem->setData(0,1,sarAssess->DataID);
//            bobjSARAssessItem->setData(1,1,34);
//            sarAssessItem->addChild(bobjSARAssessItem);
//            //Back
//            QTreeWidgetItem* backSARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("背景图像")),35);
//            backSARAssessItem->setData(0,1,sarAssess->DataID);
//            backSARAssessItem->setData(1,1,35);
//            sarAssessItem->addChild(backSARAssessItem);
//            //Fill1
//            QTreeWidgetItem* fill1SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("真目标回填图像")),36);
//            fill1SARAssessItem->setData(0,1,sarAssess->DataID);
//            fill1SARAssessItem->setData(1,1,36);
//            sarAssessItem->addChild(fill1SARAssessItem);
//            //FillBack1
//            QTreeWidgetItem* fillback1SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含真目标回填图像")),37);
//            fillback1SARAssessItem->setData(0,1,sarAssess->DataID);
//            fillback1SARAssessItem->setData(1,1,37);
//            sarAssessItem->addChild(fillback1SARAssessItem);
//            //Fill2
//            QTreeWidgetItem* fill2SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("示假目标回填图像")),38);
//            fill2SARAssessItem->setData(0,1,sarAssess->DataID);
//            fill2SARAssessItem->setData(1,1,38);
//            sarAssessItem->addChild(fill2SARAssessItem);
//            //FillBack2
//            QTreeWidgetItem* fillback2SARAssessItem = new QTreeWidgetItem(sarAssessItem,QStringList(QString("包含示假目标回填图像")),39);
//            fillback2SARAssessItem->setData(0,1,sarAssess->DataID);
//            fillback2SARAssessItem->setData(1,1,39);
//            sarAssessItem->addChild(fillback2SARAssessItem);
//        }
//    }
    //tree->setItemsExpandable(false);
    tree->expandAll();
}
