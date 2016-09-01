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
