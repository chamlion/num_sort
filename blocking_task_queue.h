#ifndef BLOCKING_TASK_QUEUE_H
#define BLOCKING_TASK_QUEUE_H
//这里有借鉴 陈硕muduo库中BlockingQueue的实现
//这里的条件变量 互斥量没有自己封装 而是直接采用了stl库中的实现
//time 2016.9.6 21:51
//author:张洲
//mail: chamlionchina@gmail.com
#include <deque>
#include <mutex>
//#include <cstddef> //size_t
#include "functions.h"
#include <iostream>
#include <pthread.h>
#include <condition_variable> 
namespace num
{  
  template<typename T>
  class blocking_task_queue : public num::noncopyable
  {
     public:
      blocking_task_queue():
      mutex_(),queue_()
      {
      }
     T take()
    {
  std::unique_lock<std::mutex> lock(mutex_);
   while (empty())
  {
    not_empty.wait(lock);
  }
   T front(queue_.front());
    queue_.pop_front();
   //std::cout<<"take  "<<front<<std::endl;
    return front;
     }
     void  put(const T x)
   {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push_back(x);
   //std::cout<<"put  "<<x<<std::endl;
   not_empty.notify_one();
 
   }
     size_t  size() //const
   {
      std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
   }
     bool empty() const
    {   
        
        return queue_.empty();
     }
     private :
     std::mutex mutex_; 
     std::deque<T>     queue_;
     std::condition_variable  not_empty;

  };
}
#endif
