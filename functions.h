#ifndef NUM_BASE_CREATE_H
#define NUM_BASE_CREATE_H
#include<unistd.h>
#include<iostream>
#include <ctime>

#define MAX_PATH 256
bool GetPathHere(std::string& path_here);
namespace num
{
/*
noncopyable源码来源于boost库，核心思想：使基类的拷贝赋值构造函数private。
他的派生类是没有访问权限的。也就无法通过拷贝以及赋值来构造新对象。
*/
class noncopyable
  {
   protected:
      noncopyable() {}
      ~noncopyable() {}
   private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      const noncopyable& operator=( const noncopyable& );
  };
class time_past:public num::noncopyable
  {
   public:
   time_past():
   start_(clock()),duration(0)
   {}
 ~time_past();
   private:
   clock_t start_, finish_;  
   double duration;
   };
}
#endif


