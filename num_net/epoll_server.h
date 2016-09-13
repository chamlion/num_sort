#ifndef epoll_server_H
#define epoll_server_H
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <queue>
#include <fstream>
/*
epoll_server实现的功能：
封装了epoll 实现对多个client中的数据的排序 
包括以下几个函数 
1)构造函数：epoll_server(short port,int client_num,std::string file_name):
port指定服务器使用的端口 client_num 指定要将要连接的主机上的数量 file_name 排序结果输出文件名
2)socket_init(): 初始化socket
2)handleread: 读取并处理client端发来数据
4)handle_sort: 对读取的数据进行K路归并排序
*/
namespace num
{
typedef std::vector<struct epoll_event> EventList;
#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)
  class epoll_server
  {
     public:
     epoll_server()
     {
     socket_init();
     }
     
     explicit epoll_server(short port,int client_num,std::string file_name):
     port_(port),client_num_(client_num),sort_flag(false),client_num_exist(client_num)
     {
     socket_init();
     out.open(file_name);
     }
     void socket_init();
     void loop();
     private:
     int  handle_read();
     void handle_sort();
     void write_to_file(long num_temp);
     struct  nd_net
     {
      long num_from_client;
      int  fd; 
      bool operator < (const nd_net &a) const 
     {  
        return num_from_client>a.num_from_client;//最小值优先  
     }    
     }; 
     struct nd_net node;
     char buf_write[2] = "z";
     std::priority_queue<nd_net> que_read;
     short port_=5188;
     int idlefd;
     int listenfd;
     struct sockaddr_in servaddr;
     int on = 1;
     std::vector<int> clients;
     int epollfd;
     struct epoll_event event;
     struct sockaddr_in peeraddr;
     socklen_t peerlen;
     int connfd;
     int nready;
     std::ofstream out;
     int client_num_;
     int client_num_exist;
     bool sort_flag;
     
  };
}
#endif
