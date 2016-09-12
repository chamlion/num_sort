#include "num_sort.h"
num::num_sort::num_sort(std::string path_read,std::string path_write):
path_read_(path_read),path_write_(path_write)
{
  init();
}
void num::num_sort::init()
{
int size=sizeof(long); 
    fd = open(path_read_.c_str(), O_RDONLY); // 
    fstat(fd,&sb);//获得文件大小
        start =static_cast<char *> ( mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
        if(start == MAP_FAILED) // 判断是否映射成功 
          printf("MAP failed \n");
   //																																																																																																																																																	else
        //printf("MAP succes\n");
}
void num::num_sort::sort_()
{   
  std::cout<<path_write_<<std::endl;
      std::string str;
       long num;
     std::stringstream ss;
         for (int i=0;i<sb.st_size;i++)
       { 
          str.push_back(start[i]);
        if(start[i]=='\n')
         { ss<<str;
           ss>>num; 
           str.clear();
             vec.push_back(num);
         }
        }
      std::sort(vec.begin(),vec.end());
std::ofstream out(path_write_);
 if (out.is_open())
{      
        for(std::vector<long>::iterator it = vec.begin() ; it != vec.end() ; it++ )  
    {  
          out<< *it<<"\n";
    } 
}    out.close();
}
num::num_sort::~num_sort()
{
 munmap(start, sb.st_size); // 解除映射 
        close(fd);
}









