#ifndef NUM_NUM_SORT_H
#define NUM_NUM_SORT_H
#include"functions.h" 
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/mman.h>  
#include <sys/stat.h> 
#include <sys/types.h>
#include <string>
#include<iostream>
#include <sstream>
#include <vector> 
#include <algorithm> 
#include<fstream>
#include <memory>
namespace num
{ 
 /*
num_sort 说明：
传入参数 一个是带排序文件位置 一个是排序好的文件输出位置
排序算法采用stl sort  
文件的读取采用 mmap  
在ubuntu15.04 环境下 测试 排序100 000 000 个long型数据 通过
机器配置为cpu i5 4200H  内存 4G 硬盘 普通硬盘
大概用时=读入数据（19s）+排序用时（46s）+数据写入(8)=73s 
*/
  class num_sort:public num::noncopyable
 {
   public:
    explicit  num_sort(std::string path_read,std::string path_write);
   void sort_();
  ~num_sort();
   private:
   void init();
   std::string path_read_,path_write_;
   int fd;
   std::vector<long>  vec;
   char *start;
   struct stat sb;
 };
}
#endif
