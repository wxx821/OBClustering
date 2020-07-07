#include "systemconfig.h"

double SystemConfig::regionZoomFactor = 0.1;
double SystemConfig::minRegionZoomFactor = 0.02;
double SystemConfig::minMoveFactor = 1.0;
double SystemConfig::minRotateFactor = 1.0;

const QString SystemConfig::usingUnit = QString::fromUtf8("北京工业大学信息学部计算机学院");
const QString SystemConfig::reportTitle = QString::fromUtf8("隐身效果评估报告");

SystemConfig::SystemConfig()
{

}
