#include <stdio.h>
#include "../include/Memory.h"

Memory::Memory()
{
    //pakeitimas
}

Block& Memory::operator[](int i)
{
    return blocks[i];
}

void Memory::print()
{
    for(int i = 0; i < MEMORY_BLOCK_COUNT; ++i)
    {
        printf("\e[1m%2X: \e[0m", i);
        for(int j = 0; j < BLOCK_LENGTH; ++j)
        {
            blocks[i][j].print();
        }
        printf("\n");
    }
}

Memory::~Memory()
{

}