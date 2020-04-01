#include "VirtualMachine.h"

VirtualMachine::VirtualMachine()
{
    this->running = true;
}

void VirtualMachine::execute()
{
    std::cout << "Hello, guys";
}

void VirtualMachine::run()
{
    while(this->running)
    {
        this->execute();
    }
}

VirtualMachine::~VirtualMachine()
{

}