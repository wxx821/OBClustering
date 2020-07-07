#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H
#include <QString>

class SystemConfig
{
public:
    SystemConfig();

    static double regionZoomFactor;
    static double minRegionZoomFactor;
    static double minMoveFactor;
    static double minRotateFactor;

    static const QString usingUnit;
    static const QString reportTitle;
};

#endif // SYSTEMCONFIG_H
