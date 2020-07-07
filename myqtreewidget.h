#ifndef MYQTREEWIDGET_H
#define MYQTREEWIDGET_H

#include <QString>
#include <QMap>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>

#include <QWidget>

class MyQTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit MyQTreeWidget(QWidget *parent = nullptr);

    QMap<QString, QTreeWidgetItem*> itemmap;

    void addItem(QStringList item, QString parentKey, QString theKey);

signals:

public slots:
};

#endif // MYQTREEWIDGET_H
