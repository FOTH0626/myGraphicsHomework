cmake_minimum_required(VERSION 3.15)

project (myLittleRenderer)

set(CMAKE_CXX_STANDARD 17)

#include_directories("/usr/include/json/json.h")
#link_directories("/usr/lib/x86_64-linux-gnu/libjsoncpp.so")
include_directories("/usr/include/json")
link_directories("/usr/lib/x86_64-linux-gnu")


find_package(Eigen3 REQUIRED)
#find_package(jsoncpp REQUIRED)

add_executable(chinaMap
main.cpp
constant.h constant.cpp
TGAImage.cpp TGAImage.h 
rasterizer.cpp rasterizer.h
mvp.h mvp.cpp)
target_link_libraries( chinaMap Eigen3::Eigen)
target_link_libraries( chinaMap jsoncpp)

add_executable(cohenSutherland
cohenSutherland.cpp
rasterizer.cpp rasterizer.h
constant.h constant.cpp
TGAImage.cpp TGAImage.h)
target_link_libraries(cohenSutherland Eigen3::Eigen)
