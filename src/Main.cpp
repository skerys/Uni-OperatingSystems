#include <iostream>

#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"

using namespace std;

int main()
{
    Block       block;
    RealMachine realMachine;

    block[9]    = 8555;
    block[9].print_bytes();
    block[9][2] = 255;
    block[9].print_bytes();
    return 0;
}