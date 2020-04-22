#include "RealMachine.h"

RealMachine::RealMachine() : pager(memory)
{
    pager.setup_vm_paging(vm, 0);
}

RealMachine::~RealMachine()
{

}