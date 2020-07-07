#include "reportutils.h"
#include <QObject>
#include <QDate>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "systemconfig.h"

ReportUtils::ReportUtils()
{
    tableindex = 1;
    figureindex = 1;
    word = new QWord();
}

ReportUtils::~ReportUtils(){
    delete word;
}

void ReportUtils::generateWord(QString file, DataModel *data){
    this->data = data;
    word->createNewWord(file);
    word->setPageOrientation(0);
    word->setWordPageView(3);
    word->setParagraphAlignment(0);
    word->setFontSize(25);
    word->setFontBold(true);
    word->insertMoveDown();
    word->insertText(QObject::tr(SystemConfig::reportTitle.toLocal8Bit()));
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->insertMoveDown();
    word->moveForEnd();
    word->setFontSize(11);
    word->setFontBold(false);
    word->insertText(QObject::tr(SystemConfig::usingUnit.toLocal8Bit()));
    word->insertMoveDown();
    word->insertText(QObject::tr(QDate::currentDate().toString().toLocal8Bit()));
    word->insertPage();
//    if(ri->format==1){
//        int titleindex  = 1;
//        if(ri->hasPeople && data->getPeoples().size()>0){
//            this->generatePeople(data->getPeoples(),1,QString::number(titleindex));
//            titleindex++;
//        }
//        if(ri->hasExperiment && data->getExperiments().size()>0){
//            this->generateExperiment(data->getExperiments(),1,QString::number(titleindex));
//            titleindex++;
//        }
//        if(ri->hasEquipment && data->getEquipments().size()>0){
//            this->generateEquipment(data->getEquipments(),1,QString::number(titleindex));
//            titleindex++;
//        }
//        if(ri->hasEnvironment && data->getEnvironments().size()>0){
//            this->generateEnvironment(data->getEnvironments(),1,QString::number(titleindex));
//            titleindex++;
//        }
//        if(ri->hasCamouflage && data->getCamouflages().size()>0){
//            this->generateCamouflage(data->getCamouflages(),1,QString::number(titleindex));
//            int camti = data->getCamouflages().size()+1;
//            if(data->getCamMaterials().size()>0){
//                this->generateCamMaterial(data->getCamMaterials(),2,QString::number(titleindex)+"."+QString::number(camti));
//                camti++;
//            }
//            if(data->getCamMethods().size()>0){
//                this->generateCamMethod(data->getCamMethods(),2,QString::number(titleindex)+"."+QString::number(camti));
//                camti++;
//            }
//            titleindex++;
//        }
//        if(ri->hasObject && data->getObjects().size()>0){
//            this->generateObject(data->getObjects(),1,QString::number(titleindex));
//            titleindex++;
//        }
//        if(ri->hasFObject && data->getFObjects().size()>0){
//            this->generateFObject(data->getFObjects(),1,QString::number(titleindex));
//            titleindex++;
//        }
//        if(ri->hasAssess && data->getAssesses().size()>0){
//            QList<Assess*> assesses = data->getAssesses();
//            for(int i=0;i<data->getAssesses().size();i++){
//                Assess* assess = assesses[i];
//                this->generateAssess(assess,1,QString::number(titleindex));
//                int assessti = 1;
//                if(assess->OpticesID!=""){
//                    OpticesAssess* oa = data->getOpticesAssess(assess->OpticesID);
//                    this->generateOpticesAssess(oa,2,QString::number(titleindex)+"."+QString::number(assessti));
//                    assessti++;
//                }
//                if(assess->InfraredID!=""){
//                    InfraredAssess* ia = data->getInfraredAssess(assess->InfraredID);
//                    this->generateInfraredAssess(ia,2,QString::number(titleindex)+"."+QString::number(assessti));
//                    assessti++;
//                }
//                if(assess->SARID!=""){
//                    SARAssess* sa = data->getSARAssess(assess->SARID);
//                    this->generateSARAssess(sa,2,QString::number(titleindex)+"."+QString::number(assessti));
//                    assessti++;
//                }
//                titleindex++;
//            }
//        }
//    }
//    else if(ri->format==2){
//        int titleindex = 1;
//        if(ri->hasAssess && data->getAssesses().size()>0){
//            QList<Assess*> assesses = data->getAssesses();
//            for(int i=0;i<data->getAssesses().size();i++){
//                Assess* assess = assesses[i];
//                this->generateAssess(assess,1,QString::number(titleindex));
//                int assessti = 1;
//                if(assess->OpticesID!=""){
//                    OpticesAssess* oa = data->getOpticesAssess(assess->OpticesID);
//                    this->generateOpticesAssess(oa,2,QString::number(titleindex)+"."+QString::number(assessti));
//                    int assessti2 = 1;
//                    if(ri->hasPeople && oa->PID!=""){
//                        People* people = data->getPeople(oa->PID);
//                        this->generatePeople(people,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasExperiment && oa->ExID!=""){
//                        Experiment* ex = data->getExperiment(oa->ExID);
//                        this->generateExperiment(ex,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        int assessti3 = 1;
//                        if(ex->PID!=""){
//                            People* people = data->getPeople(ex->PID);
//                            this->generatePeople(people,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        assessti2++;
//                    }
//                    if(ri->hasEquipment && oa->EqID!=""){
//                        Equipment* eq = data->getEquipment(oa->EqID);
//                        this->generateEquipment(eq,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasEnvironment && oa->EnID!=""){
//                        Environment* en = data->getEnvironment(oa->EnID);
//                        this->generateEnvironment(en,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasCamouflage && oa->AssID!=""){
//                        Camouflage* cam = data->getCamouflage(oa->AssID);
//                        this->generateCamouflage(cam,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        int assessti3 = 1;
//                        if(cam->CamMaterialID!=""){
//                            CamMaterial* cammaterial = data->getCamMaterial(cam->CamMaterialID);
//                            this->generateCamMaterial(cammaterial,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        if(cam->CamMethodID!=""){
//                            CamMethod* cammethod = data->getCamMethod(cam->CamMethodID);
//                            this->generateCamMethod(cammethod,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        assessti2++;
//                    }
//                    if(ri->hasObject && oa->ObjID!=""){
//                        Object* obj = data->getObject(oa->ObjID);
//                        this->generateObject(obj,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasFObject && oa->FObjID!=""){
//                        FObject* fobj = data->getFObject(oa->FObjID);
//                        this->generateFObject(fobj,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    assessti++;
//                }
//                //infrared
//                if(assess->InfraredID!=""){
//                    InfraredAssess* ia = data->getInfraredAssess(assess->InfraredID);
//                    this->generateInfraredAssess(ia,2,QString::number(titleindex)+"."+QString::number(assessti));
//                    int assessti2 = 1;
//                    if(ri->hasPeople && ia->PID!=""){
//                        People* people = data->getPeople(ia->PID);
//                        this->generatePeople(people,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasExperiment && ia->ExID!=""){
//                        Experiment* ex = data->getExperiment(ia->ExID);
//                        this->generateExperiment(ex,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        int assessti3 = 1;
//                        if(ex->PID!=""){
//                            People* people = data->getPeople(ex->PID);
//                            this->generatePeople(people,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        assessti2++;
//                    }
//                    if(ri->hasEquipment && ia->EqID!=""){
//                        Equipment* eq = data->getEquipment(ia->EqID);
//                        this->generateEquipment(eq,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasEnvironment && ia->EnID!=""){
//                        Environment* en = data->getEnvironment(ia->EnID);
//                        this->generateEnvironment(en,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasCamouflage && ia->AssID!=""){
//                        Camouflage* cam = data->getCamouflage(ia->AssID);
//                        this->generateCamouflage(cam,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        int assessti3 = 1;
//                        if(cam->CamMaterialID!=""){
//                            CamMaterial* cammaterial = data->getCamMaterial(cam->CamMaterialID);
//                            this->generateCamMaterial(cammaterial,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        if(cam->CamMethodID!=""){
//                            CamMethod* cammethod = data->getCamMethod(cam->CamMethodID);
//                            this->generateCamMethod(cammethod,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        assessti2++;
//                    }
//                    if(ri->hasObject && ia->ObjID!=""){
//                        Object* obj = data->getObject(ia->ObjID);
//                        this->generateObject(obj,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasFObject && ia->FObjID!=""){
//                        FObject* fobj = data->getFObject(ia->FObjID);
//                        this->generateFObject(fobj,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    assessti++;
//                }
//                //sar
//                if(assess->SARID!=""){
//                    SARAssess* sa = data->getSARAssess(assess->SARID);
//                    this->generateSARAssess(sa,2,QString::number(titleindex)+"."+QString::number(assessti));
//                    int assessti2 = 1;
//                    if(ri->hasPeople && sa->PID!=""){
//                        People* people = data->getPeople(sa->PID);
//                        this->generatePeople(people,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasExperiment && sa->ExID!=""){
//                        Experiment* ex = data->getExperiment(sa->ExID);
//                        this->generateExperiment(ex,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        int assessti3 = 1;
//                        if(ex->PID!=""){
//                            People* people = data->getPeople(ex->PID);
//                            this->generatePeople(people,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        assessti2++;
//                    }
//                    if(ri->hasEquipment && sa->EqID!=""){
//                        Equipment* eq = data->getEquipment(sa->EqID);
//                        this->generateEquipment(eq,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasEnvironment && sa->EnID!=""){
//                        Environment* en = data->getEnvironment(sa->EnID);
//                        this->generateEnvironment(en,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasCamouflage && sa->AssID!=""){
//                        Camouflage* cam = data->getCamouflage(sa->AssID);
//                        this->generateCamouflage(cam,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        int assessti3 = 1;
//                        if(cam->CamMaterialID!=""){
//                            CamMaterial* cammaterial = data->getCamMaterial(cam->CamMaterialID);
//                            this->generateCamMaterial(cammaterial,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        if(cam->CamMethodID!=""){
//                            CamMethod* cammethod = data->getCamMethod(cam->CamMethodID);
//                            this->generateCamMethod(cammethod,4,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2)+"."+QString::number(assessti3));
//                            assessti3++;
//                        }
//                        assessti2++;
//                    }
//                    if(ri->hasObject && sa->ObjID!=""){
//                        Object* obj = data->getObject(sa->ObjID);
//                        this->generateObject(obj,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    if(ri->hasFObject && sa->FObjID!=""){
//                        FObject* fobj = data->getFObject(sa->FObjID);
//                        this->generateFObject(fobj,3,QString::number(titleindex)+"."+QString::number(assessti)+"."+QString::number(assessti2));
//                        assessti2++;
//                    }
//                    assessti++;
//                }
//                titleindex++;
//            }
//        }
//    }
//    else {

//    }
    word->setVisible(true);
    word->saveAs();
    word->quitWord();
}

//void ReportUtils::generateSARAssess(SARAssess* sa, int titlelevel, QString titleindex){
//    switch (titlelevel) {
//    case 1:
//        word->insertTitle1(titleindex+" SAR评估数据");
//        break;
//    case 2:
//        word->insertTitle2(titleindex+" SAR评估数据");
//        break;
//    case 3:
//        word->insertTitle3(titleindex+" SAR评估数据");
//        break;
//    case 4:
//        word->insertTitle4(titleindex+" SAR评估数据");
//        break;
//    default:
//        break;
//    }

//    word->insertMoveDown();
//    word->setParagraphAlignment(0);
//    word->setFontSize(11);
//    word->setFontBold(false);
//    word->insertText("表"+QString::number(tableindex)+" SAR评估数据表");
//    word->intsertTable(tableindex,37,3);
//    word->setTableAutoFitBehavior(1);
//    word->setRowAlignment(tableindex,1,0);
//    word->setCellString(tableindex,1,1,"比较图像");
//    word->setCellString(tableindex,1,2,"相似度");
//    word->setCellString(tableindex,1,3,"相似度值");

//    int objfi = 0;
//    int objbackfi = 0;
//    int fobjfi = 0;
//    int fobjbackfi = 0;
//    int backobjfi = 0;
//    int backfi = 0;
//    int fill1fi = 0;
//    int fillback1fi = 0;
//    int fill2fi = 0;
//    int fillback2fi = 0;
//    if(sa->ObjFile!=""){
//        objfi = figureindex;
//        figureindex++;
//    }
//    if(sa->ObjBackFile!=""){
//        objbackfi = figureindex;
//        figureindex++;
//    }
//    if(sa->FObjFile!=""){
//        fobjfi = figureindex;
//        figureindex++;
//    }
//    if(sa->FObjBackFile!=""){
//        fobjbackfi = figureindex;
//        figureindex++;
//    }
//    if(sa->BackObjFile!=""){
//        backobjfi = figureindex;
//        figureindex++;
//    }
//    if(sa->BackFile!=""){
//        backfi = figureindex;
//        figureindex++;
//    }
//    if(sa->FillFile1!=""){
//        fill1fi = figureindex;
//        figureindex++;
//    }
//    if(sa->FillBackFile1!=""){
//        fillback1fi = figureindex;
//        figureindex++;
//    }
//    if(sa->FillFile2!=""){
//        fill2fi = figureindex;
//        figureindex++;
//    }
//    if(sa->FillBackFile2!=""){
//        fillback2fi = figureindex;
//        figureindex++;
//    }
//    //真假目标之间
//    word->setRowAlignment(tableindex,2,1);
//    QString tf = QString::fromUtf8("真目标");
//    if(objfi!=0){
//        tf += QString::fromUtf8("(图")+QString::number(objfi)+QString::fromUtf8(")");
//    }
//    tf += QString::fromUtf8("与示假目标");
//    if(fobjfi!=0){
//        tf += QString::fromUtf8("(图")+QString::number(fobjfi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,2,1,tf);
//    word->setCellString(tableindex,2,2,"灰度相似度");
//    word->setCellString(tableindex,2,3,QString::number(sa->Gray_TF));
//    word->setRowAlignment(tableindex,3,1);
//    word->setCellString(tableindex,3,1,"");
//    word->setCellString(tableindex,3,2,"色度相似度");
//    word->setCellString(tableindex,3,3,QString::number(sa->Tone_TF));
//    word->setRowAlignment(tableindex,4,1);
//    word->setCellString(tableindex,4,1,"");
//    word->setCellString(tableindex,4,2,"纹理相似度");
//    word->setCellString(tableindex,4,3,QString::number(sa->Texture_TF));
//    word->setRowAlignment(tableindex,5,1);
//    word->setCellString(tableindex,5,1,"");
//    word->setCellString(tableindex,5,2,"斑块特征相似度");
//    word->setCellString(tableindex,5,3,QString::number(sa->Feature_TF));
//    word->MergeCells(tableindex,2,1,5,1);

//    //真目标与回填之间
//    word->setRowAlignment(tableindex,6,1);
//    QString tfill = QString::fromUtf8("真目标");
//    if(objfi!=0){
//        tfill += QString::fromUtf8("(图")+QString::number(objfi)+QString::fromUtf8(")");
//    }
//    tfill += QString::fromUtf8("与回填");
//    if(fill1fi!=0){
//        tfill += QString::fromUtf8("(图")+QString::number(fill1fi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,6,1,tfill);
//    word->setCellString(tableindex,6,2,"灰度相似度");
//    word->setCellString(tableindex,6,3,QString::number(sa->Gray_TFill));
//    word->setRowAlignment(tableindex,7,1);
//    word->setCellString(tableindex,7,1,"");
//    word->setCellString(tableindex,7,2,"色度相似度");
//    word->setCellString(tableindex,7,3,QString::number(sa->Tone_TFill));
//    word->setRowAlignment(tableindex,8,1);
//    word->setCellString(tableindex,8,1,"");
//    word->setCellString(tableindex,8,2,"纹理相似度");
//    word->setCellString(tableindex,8,3,QString::number(sa->Texture_TFill));
//    word->setRowAlignment(tableindex,9,1);
//    word->setCellString(tableindex,9,1,"");
//    word->setCellString(tableindex,9,2,"斑块特征相似度");
//    word->setCellString(tableindex,9,3,QString::number(sa->Feature_TFill));
//    word->MergeCells(tableindex,6,1,9,1);

//    //假目标与回填之间
//    word->setRowAlignment(tableindex,10,1);
//    QString ffill = QString::fromUtf8("示假目标");
//    if(fobjfi!=0){
//        ffill += QString::fromUtf8("(图")+QString::number(fobjfi)+QString::fromUtf8(")");
//    }
//    ffill += QString::fromUtf8("与回填");
//    if(fill2fi!=0){
//        ffill += QString::fromUtf8("(图")+QString::number(fill2fi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,10,1,ffill);
//    word->setCellString(tableindex,10,2,"灰度相似度");
//    word->setCellString(tableindex,10,3,QString::number(sa->Gray_FFill));
//    word->setRowAlignment(tableindex,11,1);
//    word->setCellString(tableindex,11,1,"");
//    word->setCellString(tableindex,11,2,"色度相似度");
//    word->setCellString(tableindex,11,3,QString::number(sa->Tone_FFill));
//    word->setRowAlignment(tableindex,12,1);
//    word->setCellString(tableindex,12,1,"");
//    word->setCellString(tableindex,12,2,"纹理相似度");
//    word->setCellString(tableindex,12,3,QString::number(sa->Texture_FFill));
//    word->setRowAlignment(tableindex,13,1);
//    word->setCellString(tableindex,13,1,"");
//    word->setCellString(tableindex,13,2,"斑块特征相似度");
//    word->setCellString(tableindex,13,3,QString::number(sa->Feature_FFill));
//    word->MergeCells(tableindex,10,1,13,1);

//    //回填与背景之间
//    word->setRowAlignment(tableindex,14,1);
//    QString fillb = QString::fromUtf8("回填");
//    if(fill1fi!=0){
//        fillb += QString::fromUtf8("(图")+QString::number(fill1fi)+QString::fromUtf8(")");
//    }
//    fillb += QString::fromUtf8("与背景");
//    if(backfi!=0){
//        fillb += QString::fromUtf8("(图")+QString::number(backfi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,14,1,fillb);
//    word->setCellString(tableindex,14,2,"灰度相似度");
//    word->setCellString(tableindex,14,3,QString::number(sa->Gray_FillB));
//    word->setRowAlignment(tableindex,15,1);
//    word->setCellString(tableindex,15,1,"");
//    word->setCellString(tableindex,15,2,"色度相似度");
//    word->setCellString(tableindex,15,3,QString::number(sa->Tone_FillB));
//    word->setRowAlignment(tableindex,16,1);
//    word->setCellString(tableindex,16,1,"");
//    word->setCellString(tableindex,16,2,"纹理相似度");
//    word->setCellString(tableindex,16,3,QString::number(sa->Texture_FillB));
//    word->setRowAlignment(tableindex,17,1);
//    word->setCellString(tableindex,17,1,"");
//    word->setCellString(tableindex,17,2,"斑块特征相似度");
//    word->setCellString(tableindex,17,3,QString::number(sa->Feature_FillB));
//    word->MergeCells(tableindex,14,1,17,1);

//    //真目标与背景之间
//    word->setRowAlignment(tableindex,18,1);
//    QString tb = QString::fromUtf8("真目标");
//    if(objfi!=0){
//        tb += QString::fromUtf8("(图")+QString::number(objfi)+QString::fromUtf8(")");
//    }
//    tb += QString::fromUtf8("与背景");
//    if(backfi!=0){
//        tb += QString::fromUtf8("(图")+QString::number(backfi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,18,1,tb);
//    word->setCellString(tableindex,18,2,"灰度相似度");
//    word->setCellString(tableindex,18,3,QString::number(sa->Gray_TB));
//    word->setRowAlignment(tableindex,19,1);
//    word->setCellString(tableindex,19,1,"");
//    word->setCellString(tableindex,19,2,"色度相似度");
//    word->setCellString(tableindex,19,3,QString::number(sa->Tone_TB));
//    word->setRowAlignment(tableindex,20,1);
//    word->setCellString(tableindex,20,1,"");
//    word->setCellString(tableindex,20,2,"纹理相似度");
//    word->setCellString(tableindex,20,3,QString::number(sa->Texture_TB));
//    word->setRowAlignment(tableindex,21,1);
//    word->setCellString(tableindex,21,1,"");
//    word->setCellString(tableindex,21,2,"斑块特征相似度");
//    word->setCellString(tableindex,21,3,QString::number(sa->Feature_TB));
//    word->MergeCells(tableindex,18,1,21,1);

//    //假目标与背景之间
//    word->setRowAlignment(tableindex,22,1);
//    QString fb = QString::fromUtf8("示假目标");
//    if(fobjfi!=0){
//        fb += QString::fromUtf8("(图")+QString::number(fobjfi)+QString::fromUtf8(")");
//    }
//    fb += QString::fromUtf8("与背景");
//    if(backfi!=0){
//        fb += QString::fromUtf8("(图")+QString::number(backfi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,22,1,fb);
//    word->setCellString(tableindex,22,2,"灰度相似度");
//    word->setCellString(tableindex,22,3,QString::number(sa->Gray_FB));
//    word->setRowAlignment(tableindex,23,1);
//    word->setCellString(tableindex,23,1,"");
//    word->setCellString(tableindex,23,2,"色度相似度");
//    word->setCellString(tableindex,23,3,QString::number(sa->Tone_FB));
//    word->setRowAlignment(tableindex,24,1);
//    word->setCellString(tableindex,24,1,"");
//    word->setCellString(tableindex,24,2,"纹理相似度");
//    word->setCellString(tableindex,24,3,QString::number(sa->Texture_FB));
//    word->setRowAlignment(tableindex,25,1);
//    word->setCellString(tableindex,25,1,"");
//    word->setCellString(tableindex,25,2,"斑块特征相似度");
//    word->setCellString(tableindex,25,3,QString::number(sa->Feature_FB));
//    word->MergeCells(tableindex,22,1,25,1);

//    //包含真假目标之间
//    word->setRowAlignment(tableindex,26,1);
//    QString tbfb = QString::fromUtf8("包含真目标");
//    if(objbackfi!=0){
//        tbfb += QString::fromUtf8("(图")+QString::number(objbackfi)+QString::fromUtf8(")");
//    }
//    tbfb += QString::fromUtf8("与包含示假目标");
//    if(fobjbackfi!=0){
//        tbfb += QString::fromUtf8("(图")+QString::number(fobjbackfi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,26,1,tbfb);
//    word->setCellString(tableindex,26,2,"灰度相似度");
//    word->setCellString(tableindex,26,3,QString::number(sa->Gray_TBFB));
//    word->setRowAlignment(tableindex,27,1);
//    word->setCellString(tableindex,27,1,"");
//    word->setCellString(tableindex,27,2,"色度相似度");
//    word->setCellString(tableindex,27,3,QString::number(sa->Tone_TBFB));
//    word->setRowAlignment(tableindex,28,1);
//    word->setCellString(tableindex,28,1,"");
//    word->setCellString(tableindex,28,2,"纹理相似度");
//    word->setCellString(tableindex,28,3,QString::number(sa->Texture_TBFB));
//    word->setRowAlignment(tableindex,29,1);
//    word->setCellString(tableindex,29,1,"");
//    word->setCellString(tableindex,29,2,"斑块特征相似度");
//    word->setCellString(tableindex,29,3,QString::number(sa->Feature_TBFB));
//    word->MergeCells(tableindex,26,1,29,1);

//    //包含真目标与包含回填之间
//    word->setRowAlignment(tableindex,30,1);
//    QString tbfillb = QString::fromUtf8("真目标");
//    if(objbackfi!=0){
//        tbfillb += QString::fromUtf8("(图")+QString::number(objbackfi)+QString::fromUtf8(")");
//    }
//    tbfillb += QString::fromUtf8("与示假目标");
//    if(fillback1fi!=0){
//        tbfillb += QString::fromUtf8("(图")+QString::number(fillback1fi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,30,1,tbfillb);
//    word->setCellString(tableindex,30,2,"灰度相似度");
//    word->setCellString(tableindex,30,3,QString::number(sa->Gray_TBFillB));
//    word->setRowAlignment(tableindex,31,1);
//    word->setCellString(tableindex,31,1,"");
//    word->setCellString(tableindex,31,2,"色度相似度");
//    word->setCellString(tableindex,31,3,QString::number(sa->Tone_TBFillB));
//    word->setRowAlignment(tableindex,32,1);
//    word->setCellString(tableindex,32,1,"");
//    word->setCellString(tableindex,32,2,"纹理相似度");
//    word->setCellString(tableindex,32,3,QString::number(sa->Texture_TBFillB));
//    word->setRowAlignment(tableindex,33,1);
//    word->setCellString(tableindex,33,1,"");
//    word->setCellString(tableindex,33,2,"斑块特征相似度");
//    word->setCellString(tableindex,33,3,QString::number(sa->Feature_TBFillB));
//    word->MergeCells(tableindex,30,1,33,1);

//    //包含假目标与包含回填之间
//    word->setRowAlignment(tableindex,34,1);
//    QString fbfillb = QString::fromUtf8("真目标");
//    if(fobjbackfi!=0){
//        fbfillb += QString::fromUtf8("(图")+QString::number(fobjbackfi)+QString::fromUtf8(")");
//    }
//    fbfillb += QString::fromUtf8("与示假目标");
//    if(fillback2fi!=0){
//        fbfillb += QString::fromUtf8("(图")+QString::number(fillback2fi)+QString::fromUtf8(")");
//    }
//    word->setCellString(tableindex,34,1,fbfillb);
//    word->setCellString(tableindex,34,2,"灰度相似度");
//    word->setCellString(tableindex,34,3,QString::number(sa->Gray_FBFillB));
//    word->setRowAlignment(tableindex,35,1);
//    word->setCellString(tableindex,35,1,"");
//    word->setCellString(tableindex,35,2,"色度相似度");
//    word->setCellString(tableindex,35,3,QString::number(sa->Tone_FBFillB));
//    word->setRowAlignment(tableindex,36,1);
//    word->setCellString(tableindex,36,1,"");
//    word->setCellString(tableindex,36,2,"纹理相似度");
//    word->setCellString(tableindex,36,3,QString::number(sa->Texture_FBFillB));
//    word->setRowAlignment(tableindex,37,1);
//    word->setCellString(tableindex,37,1,"");
//    word->setCellString(tableindex,37,2,"斑块特征相似度");
//    word->setCellString(tableindex,37,3,QString::number(sa->Feature_FBFillB));
//    word->MergeCells(tableindex,34,1,37,1);

//    word->moveForEnd();
//    word->insertMoveDown();
//    tableindex++;

//    if(sa->ObjFile!=""){
//        QFileInfo photo(sa->ObjFile);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(objfi)+" 真目标图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->ObjBackFile!=""){
//        QFileInfo photo(sa->tempObjBackFile);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(objbackfi)+" 包含真目标图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->FObjFile!=""){
//        QFileInfo photo(sa->FObjFile);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(fobjfi)+" 示假目标图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->FObjBackFile!=""){
//        QFileInfo photo(sa->tempFObjBackFile);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(fobjbackfi)+" 包含示假目标图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->BackObjFile!=""){
//        QFileInfo photo(sa->BackObjFile);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(backobjfi)+" 目标背景图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->BackFile!=""){
//        QFileInfo photo(sa->tempBackFile);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(backfi)+" 背景图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->FillFile1!=""){
//        QFileInfo photo(sa->FillFile1);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(fill1fi)+" 真目标回填图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->FillBackFile1!=""){
//        QFileInfo photo(sa->FillBackFile1);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(fillback1fi)+" 包含真目标回填图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->FillFile2!=""){
//        QFileInfo photo(sa->FillFile2);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(fill2fi)+" 示假目标回填图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//    if(sa->FillBackFile2!=""){
//        QFileInfo photo(sa->FillBackFile2);
//        word->insertPic(QDir::toNativeSeparators(photo.absolutePath())+"\\"+photo.fileName());
//        word->insertMoveDown();
//        word->setParagraphAlignment(0);
//        word->setFontSize(11);
//        word->setFontBold(false);
//        word->insertText("图"+QString::number(fillback2fi)+" 包含示假目标回填图像");
//        word->insertMoveDown();
//        //figureindex++;
//    }
//}
