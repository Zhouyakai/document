#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//run the code
//./build/visual_difference ./image/1341846313.553992.png ./image/1341846313.592026.png
int main(int argc, char** argv)
{
    // 定义像素差阈值，用于过滤出动态区域
    double pixel_threshold = 50.0;

    // 加载两幅图片
    Mat ref_image = imread(argv[1], IMREAD_COLOR);
    Mat test_image = imread(argv[2], IMREAD_COLOR);

    // 如果加载图片失败，则输出错误信息并退出程序
    if(ref_image.empty() || test_image.empty())
    {
        cout << "Failed to load image file!" << endl;
        return -1;
    }

    // 如果两幅图片的大小不一致，则输出错误信息并退出程序
    if(ref_image.size() != test_image.size())
    {
        cout << "The size of two images are different!" << endl;
        return -2;
    }

    // 计算两幅图片的差分图像
    Mat diff_image;
    absdiff(ref_image, test_image, diff_image);
    imshow("diff_image", diff_image);

    // 将差分图像转换成灰度图像
    Mat gray_diff_image;
    cvtColor(diff_image, gray_diff_image, COLOR_BGR2GRAY);

    // 对灰度差分图像进行二值化处理，分离出动态区域
    Mat binary_diff_image;
    threshold(gray_diff_image, binary_diff_image, pixel_threshold, 255, THRESH_BINARY);
    imshow("gray_diff_image", gray_diff_image);
    imshow("binary_diff_image", binary_diff_image);
    // 对二值化后的差分图像进行形态学处理，消除噪声
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    morphologyEx(binary_diff_image, binary_diff_image, MORPH_OPEN, kernel);
    imshow("Noise_cancellation_binary_diff_image", binary_diff_image);

    // 对分离出的动态区域进行边缘检测，得到轮廓
    vector<vector<Point>> contours;
    findContours(binary_diff_image, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 绘制矩形框，将动态区域框出
    Mat result_image = test_image.clone();
    for(int i=0; i< contours.size(); ++i)
    {
        Rect rect = boundingRect(contours[i]);
        rectangle(result_image, rect, Scalar(0, 255, 0), 2);
    }

    // 显示结果图片
    imshow("Dynamic Region Detection Result", result_image);
    waitKey(0);
    
    return 0;  
}
