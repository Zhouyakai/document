cmake_minimum_required(VERSION 2.8)

project(converter_mask)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Boost REQUIRED COMPONENTS
# regex
filesystem   # 我的工程中只使用了 boost 的 filesystem 功能,因此这里只有一个组件
)
if(NOT Boost_FOUND)
    message("Not found Boost")
endif()
 
include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")
 

# 寻找OpenCV库
find_package(OpenCV REQUIRED)
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(converter_mask converter_mask.cpp)
# 链接OpenCV库
target_link_libraries(converter_mask ${OpenCV_LIBS})
target_link_libraries(converter_mask ${Boost_LIBRARIES})
