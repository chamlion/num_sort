#include <memory>
#include <num/net/sock_client.h>
int main()
{  //short port=6666;
std::shared_ptr<num::sock_client> client(new num::sock_client(6666,"127.0.0.1","data1.txt"));
client->loop();
}
