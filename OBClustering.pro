#-------------------------------------------------
#
# Project created by QtCreator 2020-06-16T18:15:05
#
#-------------------------------------------------

QT       += core gui
QT += axcontainer
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OBClustering
TEMPLATE = app
        INCLUDEPATH+=D:\OpenCV\include\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_calib3d348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_core348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_dnn348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_features2d348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_flann348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_highgui348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_imgcodecs348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_imgproc348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_ml348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_objdetect348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_photo348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_shape348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_stitching348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_superres348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_video348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_videoio348.dll.a\

        LIBS+=D:\OpenCV\x64\mingw\lib\libopencv_videostab348.dll.a\

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Word/qword.cpp \
        Word/reportutils.cpp \
        datamodel.cpp \
        detectionpair.cpp \
        imageadddialog.cpp \
        imageinfo.cpp \
        imagelabel.cpp \
        imageobjects.cpp \
        imagescrollarea.cpp \
        imagewidget.cpp \
        main.cpp \
        mainwindow.cpp \
        myqtreewidget.cpp \
        objectdetection.cpp \
        objectitem.cpp \
        region.cpp \
        resultwidget.cpp \
        rimagewidget.cpp \
        simagewidget.cpp \
        systemconfig.cpp \
        treewidget.cpp \
        utils.cpp \
        waitingdialog.cpp

HEADERS += \
        Word/qword.h \
        Word/reportutils.h \
        datamodel.h \
        detectionpair.h \
        imageadddialog.h \
        imageinfo.h \
        imagelabel.h \
        imageobjects.h \
        imagescrollarea.h \
        imagewidget.h \
        mainwindow.h \
        myqtreewidget.h \
        objectdetection.h \
        objectitem.h \
        region.h \
        resultwidget.h \
        rimagewidget.h \
        simagewidget.h \
        systemconfig.h \
        treewidget.h \
        ui_mainwindow.h \
        utils.h \
        waitingdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    OBClustering.pro.user
