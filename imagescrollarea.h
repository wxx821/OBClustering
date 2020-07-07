#ifndef IMAGESCROLLAREA_H
#define IMAGESCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QKeyEvent>

class ImageScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ImageScrollArea(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);//键盘按下事件
    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件

signals:

public slots:
};

#endif // IMAGESCROLLAREA_H
