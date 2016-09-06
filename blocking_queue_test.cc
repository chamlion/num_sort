#include <iostream>
#include <thread>
#include "blocking_task_queue.h"
using namespace num;
blocking_task_queue<int> *que=new blocking_task_queue<int>; 
void push()
{
  for (int i=0;i<10;i++)
  {
  que->put(i);
//std::cout<<"put  "<<i<<std::endl;
  }
}
void take()
{
  for (int i=0;i<10;i++)
  {
//  std::cout<<"take  "<<que->take()<<std::endl;
  }
}
int main()
{ 
    std::thread t1(push);
    std::thread t2(push);
    std::thread t3(take);
    std::thread t4(take);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
 std::cout<<"ok"<<std::endl;

}
