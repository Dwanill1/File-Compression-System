#include "HCTree.hpp"
#include <stdio.h>
#include "Helper.hpp"
#include <fstream>
int main(int argc, char* argv[]) 
{
    if(argc != 3)
    {
        cerr << "Error" << endl;
    }
    HCTree* tree = new HCTree();
    FancyInputStream fs (argv[1]);
    int sum = 0;
    if(fs.filesize() == 0)
    {
        FancyOutputStream output (argv[2]);
        return 0;
    }
    FancyOutputStream output (argv[2]);
    vector<int> vec(256, 0);
    for(int i = 0; i < 256; i++)
    {
        int num = fs.read_int();
        vec[i] = num;
        sum = sum + num;
    }
    tree -> build(vec);
    for(int i = 0; i < sum; i++)
    {
       output.write_byte(tree -> decode(fs));
    }
    delete tree;
    return 0;
}


