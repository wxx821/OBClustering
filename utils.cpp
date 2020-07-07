#include "utils.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QDebug>

using namespace std;

Utils::Utils(){

}

void Utils::cloneRegion(Region* region1, Region* region2, cv::Point cp, int width, int height){
    //region2 = new Region();
    region2->X = region1->X;
    region2->Y = region1->Y;
    region2->Time = region1->Time;
    region2->VNum = region1->VNum;
    region2->type = region1->type;
    region2->Intro = region1->Intro;
    region2->ObjID = region1->ObjID;
    region2->ObjType = region1->ObjType;
    region2->DataID = region1->DataID;
    region2->Angle = region1->Angle;

    QVector<cv::Point*> temppoly;
    for(int i=0;i<region1->poly.size();i++){
        cv::Point* p = new cv::Point(region1->poly[i]->x,region1->poly[i]->y);
        temppoly.push_back(p);
    }

    region2->setPoly(temppoly);

    //cv::Point cp2 = cv::Point(width/2,height/2);
    region2->setCentralPoint(cp, width, height);
}

void Utils::cloneRegion(Region* region1, Region* region2, int offsetx, int offsety){
    //region2 = new Region();
    region2->X = region1->X;
    region2->Y = region1->Y;
    region2->Time = region1->Time;
    region2->VNum = region1->VNum;
    region2->type = region1->type;
    region2->Intro = region1->Intro;
    region2->ObjID = region1->ObjID;
    region2->ObjType = region1->ObjType;
    region2->DataID = region1->DataID;
    region2->Angle = region1->Angle;

    QVector<cv::Point*> temppoly;
    for(int i=0;i<region1->poly.size();i++){
        cv::Point* p = new cv::Point(region1->poly[i]->x-offsetx,region1->poly[i]->y-offsety);
        temppoly.push_back(p);
    }

    region2->setPoly(temppoly);

    //cv::Point cp = cv::Point(width/2,height/2);
    //region2->setCentralPoint2(cp,width,height);
}

void Utils::cloneRegion(Region* region1, Region* region2){
    //region2 = new Region();
    region2->X = region1->X;
    region2->Y = region1->Y;
    region2->Time = region1->Time;
    region2->VNum = region1->VNum;
    region2->type = region1->type;
    region2->Intro = region1->Intro;
    region2->ObjID = region1->ObjID;
    region2->ObjType = region1->ObjType;
    region2->DataID = region1->DataID;
    region2->Angle = region1->Angle;

    QVector<cv::Point*> temppoly;
    for(int i=0;i<region1->poly.size();i++){
        cv::Point* p = new cv::Point(region1->poly[i]->x,region1->poly[i]->y);
        temppoly.push_back(p);
    }

    region2->setPoly(temppoly);
    //region2->setCentralPoint(cp, width, height);
}

bool Utils::checkInt(QString str){
    bool isInt = true;
    string str1 = str.toStdString();
    if(str.size()==0)
        return false;
    for (int i = 0;i < str1.size();i++) {
        if (str1.at(i) > '9' || str1.at(i) < '0'){
            isInt = false;
            break;
        }
    }
    return isInt;
}

bool Utils::checkNumber(QString str){
    bool isNumber = false;
    str.toDouble(&isNumber);
    return isNumber;
}

bool Utils::checkEmpty(QString str){
    bool isEmpty = false;
    if(str.simplified()==""){
        isEmpty = true;
    }
    return isEmpty;
}

bool Utils::checkPhone(QString str){
    bool isPhone = Utils::checkInt(str) && str.simplified().length()>=11;
    return isPhone;
}

bool Utils::checkEmail(QString str){
    bool isEmail = str.contains("@") && str.contains(".");
    return isEmail;
}

//QSqlDatabase Utils::getDB(){
//    QSqlDatabase db = QSqlDatabase::database("Assesses", false);
//    if(db.isValid()){
//        return db;
//    }
//    db = QSqlDatabase::addDatabase("QODBC", "Assesses");
//    QString dbName = QDir::fromNativeSeparators(QDir::currentPath()+ "/db/Assesses.accdb");//数据库文件

//    QString dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)}; FIL={MS Access};DBQ=%1").arg(dbName);//连接字符串
//    //qDebug()<<dsn;
//    db.setDatabaseName(dsn);
//    return db;
//}

cv::Scalar Utils::getRandomColor(){
//    int icolor = (unsigned) RNG((int)time(NULL));
//    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);

    cv::RNG rng(cvGetTickCount());
    return cv::Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
}

cv::Mat Utils::QImageToMat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        //cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        break;
    }

    return mat;
}

QImage Utils::MatToQImage(const cv::Mat& mat, QImage imgLabel)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        //QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        imgLabel = QImage(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        imgLabel.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            //image.setColor(i, qRgb(i, i, i));
            imgLabel.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            //uchar *pDest = image.scanLine(row);
            uchar *pDest = imgLabel.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        //return image;
        return imgLabel;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        //QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        imgLabel = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return imgLabel.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        //qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        //QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        imgLabel = QImage(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return imgLabel.copy();
    }
    else
    {
        //qDebug() << "ERROR: Mat could not be converted to QImage.";
        return imgLabel;
    }
}

cv::Mat Utils::fill1(cv::Mat mat, Region* region){
    cv::Mat dst;
    if(!mat.empty() && (region!=nullptr || region!=0)){
        cv::Mat mask = Utils::getMask(mat, region);
        cv::inpaint(mat, mask, dst, 5, cv::INPAINT_NS);
        return dst;
    }
    return dst;
}

cv::Mat Utils::fill2(cv::Mat mat, Region* region){
    cv::Mat dst;
    if(!mat.empty() && (region!=nullptr || region!=0)){
        cv::Mat mask = Utils::getMask(mat, region);
        cv::inpaint(mat, mask, dst, 5, cv::INPAINT_TELEA);
        return dst;
    }
    return dst;
}

double Utils::getGrayDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2){
    double degree = 0;
    if(!mat1.empty() && !mat2.empty()){
        cv::Mat gray1, gray2;
        cv::cvtColor(mat1, gray1, cv::COLOR_BGR2GRAY);
        cv::cvtColor(mat2, gray2, cv::COLOR_BGR2GRAY);
        int histSize = 255;
        float range[] = { 0,255 };
        const float* histRanges = { range };
        cv::Mat hist1, hist2;
        cv::Mat mask1 = Utils::getMask(mat1,region1);
        cv::Mat mask2 = Utils::getMask(mat2,region2);
        //生成两幅图片的灰度直方图后归一化并比较
        cv::calcHist(&gray1, 1, 0, mask1, hist1, 1, &histSize, &histRanges, true, false);
        cv::calcHist(&gray2, 1, 0, mask2, hist2, 1, &histSize, &histRanges, true, false);
        cv::normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
        cv::normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
        degree = cv::compareHist(hist1, hist2, cv::HISTCMP_CORREL);
        degree = 0.5 + degree / 2;
    }
    return degree;
}

double Utils::getToneDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2){
    double degree = 0;
    if(!mat1.empty() && !mat2.empty()){
        cv::Mat dst1, dst2;
        cv::cvtColor(mat1, dst1, cv::COLOR_BGR2HSV);
        cv::cvtColor(mat2, dst2, cv::COLOR_BGR2HSV);
        //定义直方图计算所需要的各种参数
        int h_bins = 50;
        int s_bins = 60;
        int histSize[] = { h_bins,s_bins };
        float h_ranges[] = { 0,180 };
        float s_ranges[] = { 0,256 };
        const float* ranges[] = { h_ranges, s_ranges };
        int channels[] = { 0,1 };
        cv::MatND hist1;
        cv::MatND hist2;
        cv::Mat mask1 = Utils::getMask(mat1, region1);
        cv::Mat mask2 = Utils::getMask(mat2, region2);
        //计算直方图并归一化处理
        cv::calcHist(&dst1, 1, channels, mask1, hist1, 2, histSize, ranges, true, false);
        cv::normalize(hist1, hist1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

        cv::calcHist(&dst2, 1, channels, mask2, hist2, 2, histSize, ranges, true, false);
        cv::normalize(hist2, hist2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

        degree = cv::compareHist(hist1, hist2, cv::HISTCMP_CORREL);

        degree = 0.5 + degree / 2;
    }
    return degree;
}

double Utils::getTextureDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2){
    double degree = 0;
    if(!mat1.empty() && !mat2.empty()){
        double C1 = 6.5025, C2 = 58.5225;
        if(region1!=nullptr || region1!=0){
            mat1 = region1->getSubMat(mat1);
        }
        if(region2!=nullptr || region2!=0){
            mat2 = region2->getSubMat(mat2);
        }
        int width = mat1.cols;
        int height = mat1.rows;
        int width2 = mat2.cols;
        int height2 = mat2.rows;
        if(width > width2){
            width = width2;
        }
        if(height > height2){
            height = height2;
        }
        double mean_x = 0;
        double mean_y = 0;
        double sigma_x = 0;
        double sigma_y = 0;
        double sigma_xy = 0;
        for (int v = 0; v < height; v++)
        {
            for (int u = 0; u < width; u++)
            {
                mean_x += mat1.at<uchar>(v, u);
                mean_y += mat2.at<uchar>(v, u);

            }
        }
        mean_x = mean_x / width / height;
        mean_y = mean_y / width / height;
        for (int v = 0; v < height; v++)
        {
            for (int u = 0; u < width; u++)
            {
                sigma_x += (mat1.at<uchar>(v, u) - mean_x) * (mat1.at<uchar>(v, u) - mean_x);
                sigma_y += (mat2.at<uchar>(v, u) - mean_y) * (mat2.at<uchar>(v, u) - mean_y);
                sigma_xy += abs((mat1.at<uchar>(v, u) - mean_x) * (mat2.at<uchar>(v, u) - mean_y));
            }
        }
        sigma_x = sigma_x / (width * height - 1);
        sigma_y = sigma_y / (width * height - 1);
        sigma_xy = sigma_xy / (width * height - 1);
        double fenzi = (2 * mean_x * mean_y + C1) * (2 * sigma_xy + C2);
        double fenmu = (mean_x * mean_x + mean_y * mean_y + C1) * (sigma_x + sigma_y + C2);
        degree = fenzi / fenmu;
    }
    return degree;
}

double Utils::getFeatureDegree(cv::Mat mat1, Region* region1, cv::Mat mat2, Region* region2){
    double degree = 0;
    if(!mat1.empty() && !mat2.empty()){
        if(region1!=nullptr || region1!=0){
            mat1 = region1->getSubMat(mat1);
        }
        if(region2!=nullptr || region2!=0){
            mat2 = region2->getSubMat(mat2);
        }
        //1.缩小尺寸
        //将图片缩小到8x8的尺寸，总共64个像素。
        //这一步的作用是去除图片的细节，只保留结构、明暗等基本信息，摒弃不同尺寸、比例带来的图片差异。
        cv::Mat matDst1, matDst2;
        cv::resize(mat1, matDst1, cv::Size(8, 8), 0, 0, cv::INTER_CUBIC);
        cv::resize(mat2, matDst2, cv::Size(8, 8), 0, 0, cv::INTER_CUBIC);
        //2.简化色彩
        //将缩小后的图片，转为64级灰度。也就是说，所有像素点总共只有64种颜色。
        cv::cvtColor(matDst1, matDst1, cv::COLOR_BGR2GRAY);
        cv::cvtColor(matDst2, matDst2, cv::COLOR_BGR2GRAY);
        //3.计算平均值
        //计算所有64个像素的灰度平均值。
        int iAvg1 = 0, iAvg2 = 0;
        int arr1[64], arr2[64];
        for (int i = 0; i < 8; i++) {
            uchar* data1 = matDst1.ptr<uchar>(i);
            uchar* data2 = matDst2.ptr<uchar>(i);

            int tmp = i * 8;

            for (int j = 0; j < 8; j++) {
                int tmp1 = tmp + j;

                arr1[tmp1] = data1[j] / 4 * 4;
                arr2[tmp1] = data2[j] / 4 * 4;

                iAvg1 += arr1[tmp1];
                iAvg2 += arr2[tmp1];
            }
        }
        iAvg1 /= 64;
        iAvg2 /= 64;
        //4.比较像素的灰度
        //将每个像素的灰度，与平均值进行比较。大于或等于平均值，记为1；小于平均值，记为0。
        for (int i = 0; i < 64; i++) {
            arr1[i] = (arr1[i] >= iAvg1) ? 1 : 0;
            arr2[i] = (arr2[i] >= iAvg2) ? 1 : 0;
        }
        //5.计算哈希值
            //将上一步的比较结果，组合在一起，就构成了一个64位的整数，这就是这张图片的指纹。
        //组合的次序并不重要，只要保证所有图片都采用同样次序就行了。
        int iDiffNum = 0;
        for (int i = 0; i < 64; i++)
            if (arr1[i] != arr2[i])
                ++iDiffNum;
        degree = 1 - double(iDiffNum / 64.0);
    }
    return degree;
}

cv::Mat Utils::getMask(cv::Mat mat, Region *region){
    cv::Mat mask = mat.clone();
    mask = cv::Mat::zeros(mask.size(), CV_8UC1);
    if(region == nullptr || region == 0){
        cv::Rect r(0,0,mask.cols-1, mask.rows-1);
        mask(r).setTo(255);
    }
    else{
        for (int i = 0; i < mask.rows; ++i){
            for (int j = 0; j < mask.cols; ++j){
                if(region->isInner(cv::Point(j,i))){
                    //对第0个通道进行赋值操作，也就是blue通道
                    *(mask.data + mask.step[0] * i + mask.step[1] * j + mask.elemSize1() * 0) = 255;
                    //对第2个通道进行赋值操作，也就是green通道
                    *(mask.data + mask.step[0] * i + mask.step[1] * j + mask.elemSize1() * 1) = 255;
                    //对第3个通道进行赋值操作，也就是red通道
                    *(mask.data + mask.step[0] * i + mask.step[1] * j + mask.elemSize1() * 2) = 255;
                }
                else{
                    //对第0个通道进行赋值操作，也就是blue通道
                    *(mask.data + mask.step[0] * i + mask.step[1] * j + mask.elemSize1() * 0) = 0;
                    //对第2个通道进行赋值操作，也就是green通道
                    *(mask.data + mask.step[0] * i + mask.step[1] * j + mask.elemSize1() * 1) = 0;
                    //对第3个通道进行赋值操作，也就是red通道
                    *(mask.data + mask.step[0] * i + mask.step[1] * j + mask.elemSize1() * 2) = 0;
                }
            }
        }
    }
    return mask;
}
