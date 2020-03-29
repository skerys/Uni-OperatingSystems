#include "VM.h"

VM::VM()
{
    this->running = true;
}

void VM::execute()
{
    std::cout << "Hello, guys";
}

void VM::run()
{
    while(this->running)
    {
        this->execute();
    }
}

VM::~VM()
{

}