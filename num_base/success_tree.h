#ifndef  SUCCESS_TREE_H
#define  SUCCESS_TREE_H
//查了一些资料 可以考虑败者树为K路归并排序做优化
//优先级队列 其内部采用堆来维护 其时间复杂度为O（Nlogn）
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <cstdio> //snprintf
#include "functions.h"
#include <stack>
namespace num
{
 class take_num_from_file  //从文件中读取数据
{
public:
long num;
explicit take_num_from_file(std::string str)
{
   fin.open(str,std::ios::in);
}

 bool get_a_num()
{
 std::stringstream ss; 
 std::string s; 
 if (getline(fin,s))
{ 
 //cout<<s<<endl;
 ss<<s;
 ss>>num;
//cout<<i<<endl;
 return true;
}
else
{
return false;
} 
}
private:
std::ifstream fin;
};

class success_tree
{
 public:
explicit success_tree(std::vector<std::string> files):
files_(files)
{
   create();
}
 void  create();
 
 bool sort();
 private:
  struct nd
  {  
    long  num_in_file;
    int file_index;  
    bool operator < (const nd &a) const 
    {  
        return num_in_file>a.num_in_file;//最小值优先  
    }  
  };
  struct nd node;
  std::vector<take_num_from_file*> num_source; 
  std::priority_queue<nd> ques;
  std::vector<std::string> files_;
  void adjust();
  
  //priority_queue<long> ques
};
}
#endif



