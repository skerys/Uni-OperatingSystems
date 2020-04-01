#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <memory>
#include <vector>
#include "Block.h"

#define MEMORY_BLOCK_COUNT 16


class Memory
{
private:
    Block blocks[MEMORY_BLOCK_COUNT];
public:
    Memory();
    ~Memory();
    void print();
};

#endif
