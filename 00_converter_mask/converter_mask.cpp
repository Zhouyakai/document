#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv) {
  path folder_path = argv[1];
  directory_iterator end_itr; // 默认构造函数将迭代器设置为结束位置
  for (directory_iterator itr(folder_path); itr != end_itr; ++itr)
  {
      if (is_regular_file(itr->status())) // 如果是普通文件
      {
          path file_path = itr->path();
          std::string extension = file_path.extension().string();
          if (extension == ".png") // 如果是图片文件
          {
              std::string filename = file_path.filename().string();
              cv::Mat image;
              std::cout << file_path << std::endl;
              image = cv::imread(file_path.string(), 0);
              std::cout << image.rows << image.cols << std::endl;
              std::cout << image.at<uchar>(0, 0) << std::endl;
              for (int i = 0; i < image.rows; i++) {
                for (int j = 0; j < image.cols; j++) {
                    // 访问像素值
                    int pixel_value = image.at<uchar>(i, j);
                    // 在此处进行处理操作
                    if (pixel_value == 0 )
                    {
                      image.at<uchar>(i, j) = 255;
                    }
                }
              }
              cv::imwrite("/home/yakai/study/00_converter_mask/mask/" + filename, image);  
          }
      }
  }
  return 0;
}