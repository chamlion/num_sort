#include<iostream>
#include"thread_poll.h"
#include<thread>
#include<memory>
#include<vector>
#include "num_sort.h"
#include "functions.h"
/*
测试说明： split -l 1000000 out.txt -d -a 2 data_  将原数据分割
保存在data文件夹下

*/
int main()
{ 
  std::shared_ptr<num::time_past> newtime(new num::time_past);
  std::vector<std::string> datas;
  std::string str;
  num:: get_all_file_name(datas);
  std::shared_ptr<num::thread_poll> pool(new num::thread_poll(4));
 std::vector<num::num_sort*> sorts;
  pool->start();
//std::cout<<"poll start ok"<<std::endl;
for(auto iter=datas.begin();iter != datas.end();iter++)
{
 // std::string path_read("data/"+*iter);
 // std::string path_write("data/result"+(*iter));
//std::cout<<"before push_back"<<std::endl;
//std::cout<<*iter<<std::endl;
  sorts.push_back( new num::num_sort(("data/"+*iter),("data/result_"+(*iter))));
//std::cout<<"after push_back"<<std::endl;
}
//std::cout<<"sorts create ok"<<std::endl;
for(auto iter=sorts.begin();iter != sorts.end();iter++)
{
  pool->run(std::bind(&num::num_sort::sort_,*iter));
}
  pool->stop();
}


