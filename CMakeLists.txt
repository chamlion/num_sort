#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#项目支持c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 项目信息
project (test)
# 指定生成目标
add_library(functions functions.cc functions.h)
# Create our application that uses our new library
add_executable(test test.cc)
# Link our executable with the new library
target_link_libraries(test functions)
