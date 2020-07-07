#ifndef REPORTUTILS_H
#define REPORTUTILS_H
#include <QString>
#include <QList>
#include "Word/qword.h"
#include "datamodel.h"

class ReportUtils
{
public:
    ReportUtils();
    ~ReportUtils();
    void generateWord(QString file, DataModel* data);

private:

    QWord* word;
    DataModel* data;
    int tableindex;
    int figureindex;
};

#endif // REPORTUTILS_H
