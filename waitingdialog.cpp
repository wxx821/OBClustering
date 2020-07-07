#include "waitingdialog.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>

using namespace std;

WaitingDialog::WaitingDialog(QWidget *parent) :
    QDialog(parent)
{
    l = new QLabel(this);
    l->setText("请稍后。。。。");
    QFont font("Microsoft YaHei", 15, 75);
    l->setFont(font);
    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(l);
    this->setLayout(lay);
}

WaitingDialog::~WaitingDialog()
{
//    delete l;
}

void WaitingDialog::setLText(QString str){
    l->setText(str);
}
