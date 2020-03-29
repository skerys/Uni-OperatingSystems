#include "VM.h"

VM::VM()
{
    this->running   = true;

}

void VM::execute()
{


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