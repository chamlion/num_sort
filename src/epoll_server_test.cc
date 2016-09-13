#include <memory>
#include <num/net/epoll_server.h>
int main()
{  short port=6666;
std::shared_ptr<num::epoll_server> server(new num::epoll_server(6666,2,"result.txt"));
server->loop();
}
