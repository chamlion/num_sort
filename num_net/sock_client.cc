 #include "sock_client.h"
 void num::sock_client::sock_init()
 {
 if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)	ERR_EXIT("socket");
 memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port_);
	servaddr.sin_addr.s_addr = inet_addr(ip_.c_str());
	if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("connect");
	addrlen = sizeof(localaddr);
	if (getsockname(sock, (struct sockaddr*)&localaddr, &addrlen) < 0)
	ERR_EXIT("getsockname");
 }
 void num::sock_client::loop()
 {      take_string_from_file* file=new take_string_from_file(file_name_);
        char sendbuf[1024] = {0};
	char recvbuf[1024] ={0};
	while(1)
	{  read(sock, recvbuf, sizeof(recvbuf));
	   if (recvbuf[0]=='z')
	   {
	     if(file->get_a_num())
	   {
	     write(sock, file->s.c_str(), strlen(file->s.c_str()));
	     memset(sendbuf, 0, sizeof(sendbuf));
	     memset(recvbuf, 0, sizeof(recvbuf));
	   }
	   else
	   break;
	   }  
	}
	close(sock);
 }
