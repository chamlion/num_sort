#ifndef SOCK_CLIENT_H
#define SOCK_CLIENT_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <memory>
#include <iostream>
#include<sstream>
#include<fstream>
#include<vector>

namespace num
{
typedef std::vector<struct epoll_event> EventList;
#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)
class take_string_from_file  //从文件中读取数据 
{
public:
std::string s; 
explicit take_string_from_file(std::string str)
{
   fin.open(str,std::ios::in);
}
 bool get_a_num()
{
 if (getline(fin,s))
{ 
 return true;
}
else
{
return false;
} 
}
private:
std::ifstream fin;
};
 class  sock_client
 {
 public:
 explicit sock_client(short port,std::string ip,std::string  file_name):
 port_(port),ip_(ip),file_name_(file_name)
 {
   sock_init();
 }
 void loop(); 
 private:
 int sock;
 std::string file_name_;
 struct sockaddr_in servaddr,localaddr;
 socklen_t addrlen;
 void sock_init();
short port_;
std::string ip_;
 };
 }
 #endif

 
 
 
 
 
 
 
 
