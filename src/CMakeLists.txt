 ADD_EXECUTABLE(num_sort_test 	num_sort_test.cc)
TARGET_LINK_LIBRARIES(num_sort_test num_base)
 ADD_EXECUTABLE(thread_poll_test 	thread_poll_test.cc)
TARGET_LINK_LIBRARIES(thread_poll_test num_base)
ADD_EXECUTABLE(blocking_queue_test 	blocking_queue_test.cc)
TARGET_LINK_LIBRARIES(blocking_queue_test num_base)
ADD_EXECUTABLE(success_tree_test 	success_tree_test.cc)
TARGET_LINK_LIBRARIES(success_tree_test num_base)
ADD_EXECUTABLE(epoll_server_test 	epoll_server_test.cc)
TARGET_LINK_LIBRARIES(epoll_server_test num_net)
ADD_EXECUTABLE(sock_client_test 	sock_client_test.cc)
TARGET_LINK_LIBRARIES(sock_client_test num_net)
