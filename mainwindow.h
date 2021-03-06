#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QPushButton>
#include <QToolButton>
#include <QToolBar>
#include <QSplitter>
#include <QGridLayout>
#include <QList>
#include <QCloseEvent>

#include "treewidget.h"
#include "imagewidget.h"
#include "simagewidget.h"
#include "rimagewidget.h"
#include "resultwidget.h"
#include "datamodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSplitter* splitter1;
    TreeWidget* tw;
    ImageWidget* iw;
    SImageWidget* siw;
    RImageWidget* riw;
    ResultWidget* rw;

    DataModel* dm;
    void mouseMoveEvent(QMouseEvent *e);

public slots:


protected:
    void closeEvent(QCloseEvent*event);

private:
    QMenuBar* menubar;
    QMenu* filemenu;
    QAction* newproject;
    QMenu* openproject;
    QAction* openfromfile;
    QAction* openfromdb;
    QAction* saveproject;
    QAction* saveasproject;
//    QAction* closeproject;
    QAction* exitApp;

    QMenu* toolmenu;
    QAction* dboperation;
    QAction* reportgeneration;

    QMenu* helpmenu;
    QAction* about;

    QToolBar* toolbar;
    QToolButton* pbNewproject;
    QToolButton* pbOpenfromfile;
    QToolButton* pbOpenfromdb;
    QToolButton* pbSaveproject;
    QToolButton* pbDBOperate;
    QToolButton* pbReportgenerate;

    QGridLayout* lay;


    QString projectfile;


    void addMyMenu();
    void addMyToolBar();

private slots:
    void newproject_Clicked();
    void openfromfile_Clicked();
    void saveproject_Clicked();
    void saveasproject_Clicked();
//    void closeproject_Clicked();
    void exitApp_Clicked();
    void reportgeneration_Clicked();
    void about_Clicked();

};

#endif // MAINWINDOW_H
