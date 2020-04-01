#include <iostream>

#include "VirtualMachine.h"
#include "Block.h"

using namespace std;

int main()
{
    Block block;
    block[9] = 8555;
    block[9].print_bytes();
    block[9][2] = 255;
    block[9].print_bytes();

    Memory mem;
    mem.print();
    
    return 0;
}