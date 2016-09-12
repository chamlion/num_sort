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
     
     explicit epoll_server(short port):
     port_(port)
     {
     socket_init();
     }
     void socket_init();
     void loop();
     private:
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
  };
}
#endif
