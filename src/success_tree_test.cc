#include <num/base/success_tree.h>
int main ()        
{
std::vector<std::string> files;
num:: get_all_file_name(files,"data");
num::success_tree tree(files);
tree.sort();
return 0;
}
