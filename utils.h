#ifndef UTILS_H
#define UTILS_H

#include <QImage>
#include <QString>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "region.h"
//分隔符

using namespace std;

class Utils
{
public:
    Utils();

    static bool checkInt(QString str);
    static bool checkNumber(QString str);
    static bool checkEmpty(QString str);
    static bool checkPhone(QString str);
    static bool checkEmail(QString str);

    static void cloneRegion(Region* region1, Region* region2, cv::Point cp, int width, int height);
    static void cloneRegion(Region* region1, Region* region2);
    static void cloneRegion(Region* region1, Region* region2, int offsetx, int offsety);

    static cv::Scalar getRandomColor();
    static cv::Mat QImageToMat(QImage image);
    static QImage MatToQImage(const cv::Mat& mat, QImage imgLabel);
    static cv::Mat fill1(cv::Mat mat, Region* region);
    static cv::Mat fill2(cv::Mat mat, Region* region);
    static double getGrayDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2);
    static double getToneDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2);
    static double getTextureDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2);
    static double getFeatureDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2);
    static cv::Mat getMask(cv::Mat mat, Region* region);

private:

};

#endif // UTILS_H
