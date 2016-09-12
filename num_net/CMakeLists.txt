#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#项目支持c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 项目信息
project (net)
add_library (epoll_server  epoll_server.cc  epoll_server.h)
add_executable (main main.cc)
target_link_libraries(main epoll_server)
