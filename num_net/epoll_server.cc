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
   while (1)
   {
	nready = epoll_wait(epollfd, &*events.begin(), static_cast<int>(events.size()), -1);
	if (nready == -1)
	{
	    if (errno == EINTR)
	    continue;	
	    ERR_EXIT("epoll_wait");
	}
	if (nready == 0)	// nothing happended
	    continue;

	if ((size_t)nready == events.size())
	    events.resize(events.size()*2);

	for (int i = 0; i < nready; ++i)
	{
		if (events[i].data.fd == listenfd)
		{
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
		std::cout<<"ip="<<inet_ntoa(peeraddr.sin_addr)<<" port="<<ntohs(peeraddr.sin_port)<<std::endl;
		clients.push_back(connfd);
		event.data.fd = connfd;
		event.events = EPOLLIN/* | EPOLLET*/;
		epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);
		}
	else if (events[i].events & EPOLLIN)	
	{
	connfd = events[i].data.fd;
	if (connfd < 0)
	continue;
	char buf[1024] = {0};
	int ret = read(connfd, buf, 1024);
        if (ret == -1)
	ERR_EXIT("read");
	if (ret == 0)			
	{
	std::cout<<"client close"<<std::endl;
	close(connfd);
	event = events[i];
	epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);
	clients.erase(std::remove(clients.begin(), clients.end(), connfd), clients.end());
	continue;
	}
	std::cout<<buf;
	write(connfd, buf, strlen(buf));
	}
	}
	}
}

