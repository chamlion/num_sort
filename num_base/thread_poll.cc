#include "thread_poll.h"
using namespace num;
thread_poll::thread_poll(int thread_num):
mutex_(),thread_num_(thread_num),running(false)
{
}
thread_poll::~thread_poll()
{
  if (running)
  {
    stop();
  }
}
void thread_poll::start()
{ running = true;
  threads.reserve(thread_num_);
  for (int i = 0; i < thread_num_; i++)
  {
    threads.push_back(new std::thread(std::bind(&thread_poll::run_in_thread, this)));
  }
}
void thread_poll::stop()
{
//running =false;
for(int i=0;i<thread_num_;i++)
{
run(std::bind(&thread_poll::quit, this));
}

for(auto iter=threads.begin();iter != threads.end();iter++)
 {
  (*iter)->join();
 }
}
void thread_poll::run(const Task& task)
{
  queue_.put(task);
}
void thread_poll::run_in_thread()
{  
//在这个地方如果程序执行到take，queue为空的情况下，则一直阻塞在take()
//这时候设置running设置为false，起不到让线程正常退出的作用，因此为了保险起见，通过添加
//一个任务让其正常退出
   while(running) 
 {
   Task task=queue_.take();
  if (task)
  {
   task();
  }
 }
}
void thread_poll::quit()
{

 running =false;
}









