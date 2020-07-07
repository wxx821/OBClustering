#include "myqtreewidget.h"

MyQTreeWidget::MyQTreeWidget(QWidget *parent) : QTreeWidget(parent)
{

}

void MyQTreeWidget::addItem(QStringList item, QString parentKey, QString theKey) {
    QTreeWidgetItem* tempitem;
    QMap<QString,QTreeWidgetItem*>::iterator iteritem = itemmap.find(parentKey);
    if (iteritem == itemmap.end()){
        tempitem = new QTreeWidgetItem(this, item);
    }
    else {
        tempitem = new QTreeWidgetItem(iteritem.value(), item);
    }
    if (!theKey.isEmpty()) {
        itemmap.insert(theKey,tempitem);
    }
}
