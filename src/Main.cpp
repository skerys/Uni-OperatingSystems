#include <iostream>

#include "Block.h"
#include "RealMachine.h"
#include "VirtualMachine.h"

using namespace std;

int main()
{
    Block           block;
    RealMachine     realMachine;
    VirtualMachine  virtualMachine;
    Memory          memory;

    block[9]    = 8555;
    block[9].print_bytes();
    block[9][2] = 255;
    block[9].print_bytes();

    virtualMachine.loadMemory(memory);
    virtualMachine.run();
    
    return 0;
}