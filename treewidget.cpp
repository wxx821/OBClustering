#include "treewidget.h"

#include <QGridLayout>
#include <QDateTime>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
#include "imageadddialog.h"

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent)
{
    this->imagecount = 1;
    this->tree = new QTreeWidget(this);
    tree->setColumnCount(1);
    tree->setHeaderLabel("导航");
    QHeaderView *head=tree->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    tree->resize(this->width(), this->height());
    connect(tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(toIW(QTreeWidgetItem*,int)));
    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(tree);
    this->setLayout(lay);

    Add_Image = new QAction(tr("添加图像"), this);
    Delete = new QAction(tr("删除"), this);
    Load_Image = new QAction(tr("载入图像"), this);
    connect(Add_Image, SIGNAL(triggered()), this, SLOT(addImage()));
    connect(Delete, SIGNAL(triggered()), this, SLOT(deleteItem()));
    connect(Load_Image, SIGNAL(triggered()), this, SLOT(loadImage()));
}

TreeWidget::~TreeWidget(){

}

void TreeWidget::resizeEvent(QResizeEvent *e){
    tree->resize(this->width(),this->height());
}

void TreeWidget::addImage(){
    //int size = tree->topLevelItemCount();
    ImageInfo* ii = new ImageInfo();
    ImageAddDialog* dialog = new ImageAddDialog(this,ii);
    dialog->exec();
    if(ii->imageName==""){
        delete ii;
    }
    else{
        this->data->isChanged = true;
        data->addImageInfo(ii);
        QTreeWidgetItem* imageItem = new QTreeWidgetItem(tree,QStringList(ii->imageName),0);
        this->imagecount++;
        imageItem->setData(0,1,ii->imageFile);
        tree->addTopLevelItem(imageItem);
        tree->expandAll();
    }
}

void TreeWidget::deleteItem(){
    QTreeWidgetItem* citem = tree->currentItem();
    if(citem!=NULL){
        QMessageBox::StandardButton rb = QMessageBox::question(this, "图像删除", "图像数据删除以后不可恢复，确定要删除吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::No){
            return;
        }
        //int type = citem->type();
        this->data->isChanged = true;
        this->data->deleteImageInfo(citem->data(0,1).toString());
        tree->removeItemWidget(citem,0);
        delete citem;
    }
    tree->expandAll();
}

void TreeWidget::toIW(QTreeWidgetItem* item,int index){
    QTreeWidgetItem* citem = tree->currentItem();
    if(citem!=NULL){
        //qDebug()<<citem->data(0,1).toString();
        siw->setSImageFile(citem->data(0,1).toString());
    }
}

void TreeWidget::loadImage(){
    QString file = QFileDialog::getOpenFileName(this,tr("载入图像"),"","*.*",0);
    if(!file.isNull()){
        QTreeWidgetItem* citem = tree->currentItem();
        if(citem!=NULL){
            this->data->isChanged = true;
            ImageInfo* ii = this->data->getImageInfo(citem->data(0,1).toString());
            ii->imageFile = file;
            citem->setData(0,1,file);
        }
    }
}

void TreeWidget::contextMenuEvent(QContextMenuEvent *){
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->setStyleSheet(QString::fromUtf8("border:0px"));
    menu->addAction(Add_Image);
    QTreeWidgetItem* citem = tree->currentItem();
    if(citem!=NULL){
        ImageInfo* ii = this->data->getImageInfo(citem->data(0,1).toString());
        menu->addAction(Delete);
        menu->addAction(Load_Image);
    }
    menu->exec(cur.pos()); //关联到光标
}

void TreeWidget::setDataModel(DataModel* data){
    this->data = data;
    this->treeInitial();
}

void TreeWidget::setImageWidget(ImageWidget* iw){
    this->iw = iw;
}

void TreeWidget::setSImageWidget(SImageWidget* siw){
    this->siw = siw;
}

void TreeWidget::setRImageWidget(RImageWidget* riw){
    this->riw = riw;
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

    QVector<ImageInfo*> iis = data->iis;
    for(int i=0;i<iis.size();i++){
        ImageInfo* ii = iis[i];
        QTreeWidgetItem* imageItem = new QTreeWidgetItem(tree,QStringList(ii->imageName),0);
        imageItem->setData(0,1,ii->imageFile);
        tree->addTopLevelItem(imageItem);
}
    tree->expandAll();
}
