#include "VirtualMachine.h"

#define _POSIX_C_SOURCE 200809L

void VirtualMachine::run()
{
    ic = 0;
    while(running)
    {
#if DEBUG_MODE
        //do_debug();
#else
    
#endif
    }
}
/*
void VirtualMachine::do_debug()
{
    printf("\nRegister values: RA: %X; RB: %X; IC:%X; SF:%X\n", ra.get_value(), rb.get_value(), ic.get_value(), sf.get_status());
    Word nextCommand = memory[ic/16][ic%16];

    if(nextCommand[2] <= 15){
        nextCommand[2] = nextCommand[2] >= 10 ? 'A' + nextCommand[2] - 10 : '0' + nextCommand[2];
    }
    if(nextCommand[3] <= 15){
        nextCommand[3] = nextCommand[3] >= 10 ? 'A' + nextCommand[3] - 10 : '0' + nextCommand[3];
    }
    printf("\nNext command: %c%c%c%c\n", nextCommand[0], nextCommand[1], nextCommand[2], nextCommand[3]);
    memory.print();

    printf("\nPress any key to run the next command...");
    std::cin.get();
    printf("\nRunning command %c%c%c%c\n", nextCommand[0], nextCommand[1], nextCommand[2], nextCommand[3]);
}*/

void VirtualMachine::set_ptr(Word word)
{
    ptr.set_value(word.get_int());
}

VirtualMachine::~VirtualMachine()
{

}