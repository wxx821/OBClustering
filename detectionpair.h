#ifndef DETECTIONPAIR_H
#define DETECTIONPAIR_H
#include <QString>
class DetectionPair
{
public:
    DetectionPair(QString filename,QString imageName);
    QString filename;
    QString imageName;
};

#endif // DETECTIONPAIR_H
