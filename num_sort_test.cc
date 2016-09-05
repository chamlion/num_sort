/*
本test包括
1）随机数的生成
2）排序 
随机数生成：范围为min～max 生成数据个数为 count
*/
#include "num_sort.h"
#include"functions.h" 
#include<memory>
int main()
{  
  long min=1000000000,max=9999999999,count=10000;
    std::string path_set="out.txt";
    std::shared_ptr<num::random_create> newrandom(new num::random_create(min,max,count,path_set));
    if ( newrandom->create())
    std::cout<<"num_create ok \n";
  std::string path_read("out.txt");
  std::string path_write("result.txt");
std::shared_ptr<num::time_past> newtime(new num::time_past);
  std::shared_ptr<num::num_sort> new_sort(new num::num_sort(path_read,path_write));
 new_sort->sort_();

}
