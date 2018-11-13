#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<cctype>

using namespace cv;
using namespace std;
RNG g_rng(12345);

int main()
{
    int countFrame = 0;
    //读入视频
    VideoCapture capture("F:\\out.avi");
    if (!capture.isOpened())
    {
        return 0;
    }

    Mat srcImage, outImage, maskImage;
    while (1)
    {
        double start = (double)getTickCount();
        if(!capture.read(srcImage)) break;
        countFrame++;

        outImage = srcImage.clone();//复制图片

        cvtColor(outImage, maskImage, CV_RGB2GRAY);//灰度化
        blur(maskImage, maskImage, Size(3, 3)); //均值滤波
        threshold(maskImage, maskImage, 100, 255, CV_THRESH_BINARY);//二值化

        //形态学闭运算处理
        Mat element1 = getStructuringElement(MORPH_RECT, Size(2, 3));
        Mat element2 = getStructuringElement(MORPH_RECT, Size(2, 2));
        erode(maskImage, maskImage, element2, cv::Point(-1, -1), 1);
        dilate(maskImage, maskImage, element1, cv::Point(-1, -1), 1);

        //遍历寻找外轮廓
        vector<vector<Point>>contours, contours2;
        findContours(maskImage, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1, Point(0, 0));

        //比较每个轮廓的面积
        vector<Moments>mu(contours.size());
        for (int i = 0; i < contours.size(); i++)
        {
            Rect rect = boundingRect(contours[i]);
            if (rect.width + 2 < rect.height&&rect.height>1.5*rect.width)//去除一些噪点和横条
                mu[i] = moments(contours[i], 0);
        }
        vector<Point2f>mc(contours.size());
        for (size_t i = 0; i < contours.size(); i++)
        {
            mc[i] = Point2f(static_cast<float> (mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m10 / mu[i].m00));
        }

        size_t i, max = 0, second = 0;//找出面积最大的两个值，即两个竖条
        for (i = 0; i < contours.size(); i++)
        {
            if (mu[i].m00>max)
                max = mu[i].m00;
        }

        for (i = 0; i < contours.size(); i++)
        {
            if (mu[i].m00>second&&mu[i].m00 < max)
                second = mu[i].m00;
        }
        for (i = 0; i < contours.size(); i++)
        {
            if (abs(mu[i].m00 - max) < 1)
                contours2.push_back(contours[i]);
            if (abs(mu[i].m00  - second) < 1)
                contours2.push_back(contours[i]);
        }
        int e = 0;
        for ( i = 0; i < contours2.size(); i++)
        {
            e++;
        }
        //cout <<max<< "\t"<<second<<"\t"<< e<<endl;

        Rect rect1 = boundingRect(contours2[0]);
        Rect rect2 = boundingRect(contours2[1]);
        Point point1 = Point(rect1.x, rect1.y);
        Point point2 = Point(rect2.x, rect2.y + rect2.height);
        //限制矩形长度，避免框到非对应的灯条
        if ( abs(point2.y - point1.y)*8>abs(point2.x - point1.x))
            if(abs(point2.x-point1.x)<122&&abs(point2.y - point1.y)*1.5<abs(point2.x - point1.x))
                rectangle(srcImage, point1,point2,Scalar(255, 0, 0), 2, 8, 0);

        imshow("src", srcImage);
        imshow("mask", maskImage);
        double end = (double)getTickCount();
        cout << "Frame: " << countFrame << "\tTime: ";
        cout<< (end - start) * 1000 / (getTickFrequency()) << "ms" << endl;

        waitKey(1);
    }
    waitKey(0);
    return 0;
}

