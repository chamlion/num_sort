#ifndef NUM_FUNCTIONS_H
#define NUM_FUNCTIONS_H
#include<unistd.h>
#include<iostream>
#include <ctime>
#include<random>
#include<fstream>
#include <dirent.h>
#define MAX_PATH 256

namespace num
{
bool GetPathHere(std::string& path_here);
void get_all_file_name(std::vector<std::string>& vec);
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
  class random_create:public num::noncopyable
   {
    public:
    random_create():
    min_(1),max_(1000000000),count_(100),path_set_("out.txt")
    {
    }
  
    explicit random_create(long min,long max,long count,std::string path_set);
    bool create();
    private:
     std::string path_set_;
     long min_;
     long max_;
     long count_; 
   };
  
}
#endif







