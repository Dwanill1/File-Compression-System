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
    FancyInputStream* fs = new FancyInputStream(argv[1]);
    if(fs -> filesize() == 0)
    {
        FancyOutputStream* output = new FancyOutputStream(argv[2]);
        delete output;
        return 0;
    }
    vector<int> vec(256, 0);
    while(true)
    {
        unsigned int num = fs -> read_byte();
        if(num == -1)
        {
            break;
        }
        vec[num] =  vec[num] + 1;
    }
    tree -> build(vec);
    FancyOutputStream output(argv[2]);
    for(int i = 0; i < 256; i++)
    {
        output.write_int(vec[i]);
    }
    fs -> reset();
    for(int i = 0; i < fs -> filesize(); i++)
    {
        unsigned char ch = fs -> read_byte();
        tree -> encode(ch , output);
    }
    delete fs;
    delete tree;
    return 0;
}

/*
int main(int argc, char* argv[])
{
    HCTree* tree  = new HCTree();
    vector<int> num(256, 0);
    num[65] = 6;
    num[66] = 4;
     num[67] = 4;
     num[71] = 1;
    num[72] = 2;

    tree -> build(num);
    FancyOutputStream fs (argv[1]);
    tree -> encode('H', fs);
   FancyInputStream fsi (argv[2]);
   tree -> decode(fsi);
    return 0;
}
*/

