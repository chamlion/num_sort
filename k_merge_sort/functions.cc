#include"functions.h"

bool num::GetPathHere(std::string& path_here)
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
void num::get_all_file_name(std::vector<std::string>& vec)
{
DIR * dir;
    struct dirent * ptr;
    int i;
dir = opendir("/home/chamlion/Documents/num_solv/test_data/data/");
    while((ptr = readdir(dir)) != NULL)
    {    if (ptr->d_name[0]!='.')
        { //std::cout<<ptr->d_name<<std::endl;
         vec.push_back(ptr->d_name);
        }
    }


    closedir(dir);
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
   std::ofstream out(path_set_); 
   if (out.is_open()) 
  {
    for (long i=count_;i>0;i--)
     {
        out<< dis(gen)<<"\n";
     } 
   out.close();
   } 
  
else
  return false; 
  return true;  
}
  















