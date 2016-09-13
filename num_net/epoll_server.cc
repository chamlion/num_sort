#include "epoll_server.h"
void num::epoll_server::socket_init()
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC); 
    if ((listenfd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP)) < 0)
    ERR_EXIT("socket");
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port=htons(port_);	//意思是打开的端口
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    ERR_EXIT("setsockopt");
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    ERR_EXIT("setsockopt");
    if (listen(listenfd, SOMAXCONN) < 0)
    ERR_EXIT("listen");
    epollfd = epoll_create1(EPOLL_CLOEXEC);
    event.data.fd = listenfd; 
    event.events = EPOLLIN/* | EPOLLET*/; 
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);
}
void num::epoll_server::loop()
{  
   EventList events(16);
   int num_connet=0;
   int ret;
   while (1)
   {    //std::cout<<"1"<<std::endl;
	nready = epoll_wait(epollfd, &*events.begin(), static_cast<int>(events.size()), -1);
	//std::cout<<"2"<<std::endl;
	if (nready == -1)
	{
	    if (errno == EINTR)
	    continue;	
	    ERR_EXIT("epoll_wait");
	}
	if (nready == 0)	// nothing happended
	    continue;
        //std::cout<<"3"<<std::endl;
	if ((size_t)nready == events.size())
	    events.resize(events.size()*2);

	for (int i = 0; i < nready; ++i)
	{
		if (events[i].data.fd == listenfd)
		{       num_connet++;
			peerlen = sizeof(peeraddr);
			connfd = ::accept4(listenfd, (struct sockaddr*)&peeraddr,&peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
			if (connfd == -1)
			{
				if (errno == EMFILE) //文件描述符用完
				{
				close(idlefd);
				idlefd = accept(listenfd, NULL, NULL);
				close(idlefd);
				idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
				continue;
				}
			else
			ERR_EXIT("accept4");
			}
		//std::cout<<"ip="<<inet_ntoa(peeraddr.sin_addr)<<" port="<<ntohs(peeraddr.sin_port)<<std::endl;
		clients.push_back(connfd);
		event.data.fd = connfd;
		event.events = EPOLLIN/* | EPOLLET*/;
		write(connfd, buf_write, strlen(buf_write));
		epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);
		}
	else if (events[i].events & EPOLLIN)	
	{
	connfd = events[i].data.fd;
	if (connfd < 0)
	continue;
	//char buf[1024] = {0};
	 //ret = read(connfd, buf, 1024);
	ret= handle_read();
        if (ret == -1)
	ERR_EXIT("read");
	if (ret == 0)			
	{
	//std::cout<<"client close"<<std::endl;
	close(connfd);
	event = events[i];
	epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);
	clients.erase(std::remove(clients.begin(), clients.end(), connfd), clients.end());
	client_num_exist--;
	if(client_num_exist==0)
	{
	 // std::cout<<"client_num_exist  "<<client_num_exist<<std::endl;
	  out.close();
	  exit(0);
	 // break;
	}
	handle_sort();
	continue;
	}
	//std::cout<<"已经链接的client  "<<num_connet<<std::endl;
	if (num_connet==client_num_)
	{
	 sort_flag=true;
	}
	if(sort_flag==true)
	{handle_sort();
	// std::cout<<"sort"<<std::endl;
	 }
	}
	}
	}
	 
}
int  num::epoll_server::handle_read()
{   // std::cout<<"1"<<std::endl;
    //保存俩信息，从该client接收到的数据和该client的fd
   char buf[1024] = {0}; //接收缓冲区
   int ret;
   long num;
   ret = read(connfd, buf, 1024);
   //std::cout<<"data read  "<<buf<<std::endl;
   if (ret<=0)
   return ret;
  // if(buff_check())
   std::string str=buf;
   std::stringstream ss; 
   ss<<str;
   ss>>num;
   node.num_from_client=num;
   node.fd=connfd;
   que_read.push(node); 
   //handle_sort();
   //std::cout<<node.fd<<"------"<<node.num_from_client<<std::endl;  
   return ret;
}
void num::epoll_server::handle_sort()
{
 write(que_read.top().fd, buf_write, strlen(buf_write));
 write_to_file(que_read.top().num_from_client);
 que_read.pop();
}
void num::epoll_server::write_to_file(long num_temp)
{
  out<<num_temp<<"\n";
}

