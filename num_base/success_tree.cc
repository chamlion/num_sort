#include "success_tree.h"
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
