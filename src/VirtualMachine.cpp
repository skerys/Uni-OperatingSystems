#include "VirtualMachine.h"

VirtualMachine::VirtualMachine()
{
    this->running = true;
}

void VirtualMachine::execute()
{
    std::cout << "Hello, guys";
}

void VirtualMachine::execute_command()
{
    
}
    
void VirtualMachine::loadMemory(Memory _memory)
{
    memory = _memory;
}

void VirtualMachine::run()
{

}

VirtualMachine::~VirtualMachine()
{

}