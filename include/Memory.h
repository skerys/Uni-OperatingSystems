#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Block.h"

class Memory
{
private:
    Block blocks[MEMORY_BLOCK_COUNT];
public:
    Block& operator[](int i);

    Memory();
    void print();
    ~Memory();
};