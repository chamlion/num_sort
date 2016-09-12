#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
#项目支持c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 项目信息
set(base_SRCS
  functions.cc 
  num_sort.cc
  thread_poll.cc
  success_tree.cc
  )

add_library(num_base ${base_SRCS})
target_link_libraries(num_base pthread rt)

install(TARGETS num_base DESTINATION lib)
set(HEADERS
  functions.h 
  num_sort.h
  thread_poll.h
  success_tree.h
  blocking_task_queue.h
  )
install(FILES ${HEADERS} DESTINATION include/num/base)

