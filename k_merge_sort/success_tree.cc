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
void num::success_tree::create()
{   

    long num;
for(auto iter=files_.begin();iter != files_.end();iter++)
   {
    num_source.push_back(new take_num_from_file("data/"+(*iter)));
   } 
     for(int i= 0;i<num_source.size();i++)
    {    
      if(num_source[i]->get_a_num())
     { 
      node.num_in_file=num_source[i]->num;
      node.file_index=i;
      ques.push(node); 
   //std::cout<<"i= "<<i<<"  ques .size "<<ques.size()<<" num_source.size"<<num_source.size()<<std::endl;
//因为这里读取的是所有排序过的文件，所以文件不 为空，
      }
     else
     std::cout<<"fail "<<i<<std::endl;
    }

}


bool num::success_tree::sort()  //每一千万行数据保存为一个文件大约一百M左右
{
  char out_file_name[20]={0};
  std::ofstream out;
   long count=0;
    int file_num=0; 
   while( !num_source.empty()  )
  { // std::cout<<ques.top()<<"\n";
       if(0==count)
    {
 snprintf(out_file_name, sizeof(out_file_name)-1,"%s%d%s","result",file_num++,".txt");   
      out.open(out_file_name);
    // std::cout<<" count=0 "<<ques.top().num_in_file<<"  file_index  "<<ques.top().file_index<<std::endl;
      out<<ques.top().num_in_file<<"\n";
      node.file_index=ques.top().file_index;
      ques.pop(); 
     if(num_source[ node.file_index]->get_a_num())
     {
      node.num_in_file=num_source[ node.file_index]->num;
      ques.push(node);
     }
      else 
     {
       num_source.erase(num_source.begin()+ node.file_index);
       adjust();
     }	
    }
     else
    {
      out<<ques.top().num_in_file<<"\n";
     //  std::cout<<" count=0 "<<ques.top().num_in_file<<"  file_index  "<<ques.top().file_index<<std::endl;
      node.file_index=ques.top().file_index;
      ques.pop(); 
     if(num_source[ node.file_index]->get_a_num())
     {
      node.num_in_file=num_source[ node.file_index]->num;
      ques.push(node);
     }
      else 
     { 
     //  std::cout<<"berore size "<<num_source.size()<<std::endl;
      // std::cout<<"delete index"<<node.file_index<<std::endl;
       num_source.erase(num_source.begin()+ node.file_index);
      std::cout<<"delete  "<<node.file_index<<"  now 剩余"<<num_source.size()<<std::endl;
       adjust();
     }		
     } 
     if (10000000==count)
    {
      out.close();
      count=-1;
    } 
   count++;
    
  } 
while(!ques.empty())
 {  
  // std::cout<<""<<std::endl;
   std::cout<<"!ques.empty"<<std::endl;
   out<<ques.top().num_in_file<<"\n";
   ques.pop();
 }
out.close();
}

void num::success_tree::adjust ()  
//优先级队列不支持遍历 只能通过栈先将里面的数据取出来，
//处理后在放回去来实现对节点信息的更新。
//由于每个文件大小为100M 10个G才100个文件左右，其对时间的消耗不大
{
 nd node_temp;
 std::stack<nd> sta;
  while(!ques.empty())
   {  node_temp.num_in_file=ques.top().num_in_file;
      node_temp.file_index=ques.top().file_index;
      if (ques.top().file_index>node.file_index)
     {  
         node_temp.file_index--;  
     }
     sta.push(node_temp);
         ques.pop();
   }
 while(!sta.empty())
 {   
     ques.push(sta.top());
//std::cout<<sta.top().file_index<<std::endl;
     sta.pop();
 }

}
/*
*/
int main ()
{
std::vector<std::string> files;
num:: get_all_file_name(files,"data");
num::success_tree tree(files);
tree.sort();
return 0;

}


