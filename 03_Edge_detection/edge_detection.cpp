#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("/home/yakai/study/03_Edge_detection/picture/person1.png"); // 读取图像
    Mat gray, edges;
    cvtColor(src, gray, COLOR_BGR2GRAY); // 转换为灰度图像

    // 执行高斯滤波和 Canny 边缘检测
    GaussianBlur(gray, gray, Size(3, 3), 0);
    Canny(gray, edges, 50, 150, 3);

    // 显示结果
    imshow("Source Image", src);
    imshow("Detected Edges", edges);
    waitKey(0);

    return 0;
}







