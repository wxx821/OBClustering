#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QAction>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QContextMenuEvent>
#include <QScrollArea>
#include <QResizeEvent>
#include <QTreeWidgetItem>
//opencv的头文件
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "myqtreewidget.h"
#include "datamodel.h"

#include "imagewidget.h"
#include "simagewidget.h"
#include "rimagewidget.h"
#include "resultwidget.h"

class TreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget();

    DataModel* data;
    ImageWidget* iw;
    SImageWidget* siw;
    RImageWidget* riw;
    ResultWidget* rw;

    QTreeWidget* tree;
    //QScrollArea* qsa;

    QAction* Add_Image;
    QAction* Delete;
    QAction* Load_Image;

    void resizeEvent(QResizeEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    void setDataModel(DataModel* data);

    void setImageWidget(ImageWidget* iw);
    void setSImageWidget(SImageWidget* siw);
    void setRImageWidget(RImageWidget* riw);
    void setResultWidget(ResultWidget* rw);


signals:

public slots:

private:
    void treeInitial();
    int imagecount;

private slots:
    void addImage();
    void deleteItem();
    void toIW(QTreeWidgetItem* item,int index);
    void loadImage();
};

#endif // TREEWIDGET_H
