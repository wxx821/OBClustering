#include "imageadddialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include "utils.h"

ImageAddDialog::ImageAddDialog(QWidget *parent, ImageInfo *ii) : QDialog(parent)
{
    this->ii = ii;
    qlImageName = new QLabel(this);
    qlImageName->setText("图像名称");
    leImageName = new QLineEdit(this);
    qlImageDescr = new QLabel(this);
    qlImageDescr->setText("图像描述");
    leImageDescr = new QTextEdit(this);
    qlImageFile = new QLabel(this);
    qlImageFile->setText("图像文件");
    leImageFile = new QLineEdit(this);
    pbSelectFile = new QPushButton(this);
    pbSelectFile->setText("浏览");
    connect(pbSelectFile, SIGNAL(clicked()), this, SLOT(select()));
    pbSubmit = new QPushButton(this);
    pbSubmit->setText("确定");
    connect(pbSubmit, SIGNAL(clicked()), this, SLOT(submit()));
    pbCancel = new QPushButton(this);
    pbCancel->setText("取消");
    connect(pbCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    lay2 = new QGridLayout(this);
    lay2->addWidget(pbSubmit,0,0,1,1);
    lay2->addWidget(pbCancel,0,1,1,1);
    widget = new QWidget(this);
    widget->setLayout(lay2);
    QGridLayout* lay = new QGridLayout(this);
    lay->addWidget(qlImageName,0,0,1,1);
    lay->addWidget(leImageName,0,1,1,1);
    lay->addWidget(qlImageDescr,1,0,1,1);
    lay->addWidget(leImageDescr,1,1,1,1);
    lay->addWidget(qlImageFile,2,0,1,1);
    lay->addWidget(leImageFile,2,1,1,1);
    lay->addWidget(pbSelectFile,2,2,1,1);
    lay->addWidget(widget,3,0,1,3);
    this->setLayout(lay);
    this->setWindowTitle("添加图像");
}

ImageAddDialog::~ImageAddDialog(){

}

void ImageAddDialog::submit(){
    if(Utils::checkEmpty(this->leImageName->text().simplified())){
        QMessageBox::warning(this, tr("数据不合法"),tr("字段不能为空: %1").arg("图像名称"));
        return;
    }
    if(Utils::checkEmpty(this->leImageFile->text().simplified())){
        QMessageBox::warning(this, tr("数据不合法"),tr("字段不能为空: %1").arg("图像文件"));
        return;
    }
    this->ii->imageName = this->leImageName->text().simplified();
    this->ii->imageDecr = this->leImageDescr->toPlainText().simplified();
    this->ii->imageFile = this->leImageFile->text().simplified();
    this->close();
}

void ImageAddDialog::cancel(){
    this->close();
}

void ImageAddDialog::select(){
    QString file = QFileDialog::getOpenFileName(this,tr("载入图像"),"","*.*",0);
    if(!file.isNull()){
        this->leImageFile->setText(file);
    }
}
