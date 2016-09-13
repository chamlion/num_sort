#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#项目支持c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 项目信息
set(net_SRCS
  epoll_server.cc 
  sock_client.cc
  )

add_library(num_net ${net_SRCS})
#target_link_libraries(num_base pthread rt)

install(TARGETS num_net DESTINATION lib)
set(HEADERS
  epoll_server.h
  sock_client.h
  )
install(FILES ${HEADERS} DESTINATION include/num/net)

