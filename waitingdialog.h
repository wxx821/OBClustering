#ifndef WAITINGDIALOG_H
#define WAITINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QString>

class WaitingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingDialog(QWidget *parent = 0);
    ~WaitingDialog();
    QLabel* l;
    void setLText(QString str);
private:

};

#endif // WAITINGDIALOG_H
