#include <opencv2/opencv.hpp>
#include <highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(){
    Mat image,mask,gray,thresh,show;
    image=imread("C://Users//zst//Desktop//elevator//1.JPG");
    if (image.empty()){
        cout<<"image is empty!"<<endl;
        return -1;
    }
    image.copyTo(show);
    Point center;
    center.x=show.cols/2;
    center.y=show.rows/2;
    circle(show, center, 3, cv::Scalar(0, 255, 255), 2);

    //预处理
    cvtColor(image, gray, CV_BGR2GRAY);
    //adaptiveThreshold(gray, mask, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY,10,2);
    threshold(gray,mask,80,255,THRESH_BINARY_INV);
    Canny(mask, mask, 3, 9, 3);
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(mask,mask,element, cv::Point(-1, -1), 1);
    imshow("mask",mask);

    //用高,宽，轮廓大小筛选
    vector<std::vector<cv::Point> >contours,contours2;
    findContours(mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));
    for (size_t i = 0; i < contours.size(); i++){
        cv::Rect rect_bound = cv::boundingRect(contours[i]);

        if (rect_bound.height>0.8*rect_bound.width
                &&rect_bound.height<1.2*rect_bound.width
                &&rect_bound.height>mask.rows/30
                &&rect_bound.height<mask.rows/8)
            contours2.push_back(contours[i]);
    }
    //画图
    cout<<"contours2.size()="<<contours2.size();
    for (uint i=0; i < contours2.size(); i++){
        Rect rect_b=boundingRect(contours2[i]);
        rectangle(show,rect_b,Scalar(0,0,255),3,8);
    }
    imshow("elevator",show);

    waitKey(0);
    return 0;
}
