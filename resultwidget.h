#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QCheckBox>
//opencv的头文件
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "datamodel.h"
#include "region.h"

class ResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultWidget(QWidget *parent = nullptr);
    ~ResultWidget();
    void setData(DataModel* dm);
    void setMat1(cv::Mat mat1, Region* region1);
    void setMat2(cv::Mat mat2, Region* region2);
    void resizeEvent(QResizeEvent *);
signals:

private slots:
    void datarefresh();
    void datarefresh2();
    void generatereport();
private:
    DataModel* data;
    cv::Mat mat1;
    cv::Mat mat2;
    Region* region1;
    Region* region2;
    QGridLayout* lay;
    QGridLayout* lay1;
    QGridLayout* lay2;
    QWidget* table1widget;
    QWidget* table2widget;
    QTabWidget* tabw;
    QTableWidget* table1;
    QTableWidgetItem* degree1;
    QTableWidgetItem* degree2;
    QTableWidgetItem* degree3;
    QTableWidgetItem* degree4;
    QCheckBox* cb1;
    QCheckBox* cb2;
    QTableWidget* table2;
    QPushButton* pbRefresh;
    QPushButton* pbRefresh2;
    QPushButton* pbGenerateReport;
};

#endif // RESULTWIDGET_H
