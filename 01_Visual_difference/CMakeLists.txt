cmake_minimum_required(VERSION 2.8)

project(visual_difference)

set(CMAKE_CXX_FLAGS "-std=c++11")

# 寻找OpenCV库
find_package(OpenCV REQUIRED)
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(visual_difference visual_difference.cpp)
# 链接OpenCV库
target_link_libraries(visual_difference ${OpenCV_LIBS})
