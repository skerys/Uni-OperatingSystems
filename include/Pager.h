#pragma once

#include "Memory.h"
#include "VirtualMachine.h"

class Pager
{
    Memory& memoryRef;

public:
    Pager(Memory& _memoryRef) : memoryRef(_memoryRef){}

    int get_real_addr(int virtualAddr, Word ptr);
    int get_read_block(int virtualBlock, Word ptr);

    void setup_vm_paging(VirtualMachine& vm, int index);
};