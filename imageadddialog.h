#ifndef IMAGEADDDIALOG_H
#define IMAGEADDDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <imageinfo.h>

class ImageAddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ImageAddDialog(QWidget *parent = nullptr, ImageInfo* ii=nullptr);
    ~ImageAddDialog();

    QLabel* qlImageName;
    QLineEdit* leImageName;
    QLabel* qlImageDescr;
    QTextEdit* leImageDescr;
    QLabel* qlImageFile;
    QLineEdit* leImageFile;
    QPushButton* pbSelectFile;
    QPushButton* pbSubmit;
    QPushButton* pbCancel;
    QGridLayout* lay;
    QGridLayout* lay2;
    QWidget* widget;

    ImageInfo* ii;

public slots:
    void submit();
    void select();
    void cancel();
};

#endif // IMAGEADDDIALOG_H
