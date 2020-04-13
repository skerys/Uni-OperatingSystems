#pragma once

#include "Memory.h"

class Pager
{
    Memory& memoryRef;

public:
    Pager(Memory& _memoryRef) : memoryRef(_memoryRef){}

    int get_real_addr(int virtual_addr, Word ptr);
};