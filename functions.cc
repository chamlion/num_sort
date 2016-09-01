#include"functions.h"

bool GetPathHere(std::string& path_here)
{  
    path_here.clear();
    char szWorkDir[MAX_PATH] = {0} ;  
  //  char szCfgFileNameTemp[MAX_PATH] = {0} ;  
    if(!getcwd(szWorkDir, 260))  
    {  
        return false ; 
    }  
 
    path_here = szWorkDir ;  
    path_here.append("/") ;  
    return true ;  
}  
num::time_past:: ~time_past()
  {
    finish_ = clock();  
    duration = (double)(finish_ - start_) / CLOCKS_PER_SEC;  
    std::cout<< duration<<"seconds used"<<std::endl;   
 }
num::random_create::random_create(long min,long max,long count,std::string path_set):
    min_(min),max_(max),count_(count),path_set_(path_set)
{
}
bool num::random_create::create()
{  std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis(min_, max_);
   std::ofstream out("out.txt"); 
   if (out.is_open()) 
  {
    for (long i=count_;i>0;i--)
     {
        out<< dis(gen)<<std::endl;
     } 
   out.close();
   } 
  
else
  return false; 
  return true;  
}
  















