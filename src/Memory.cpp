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
        printf("%2X: ", i);
        for(int j = 0; j < BLOCK_LENGTH; ++j)
        {
            printf("%4X ", blocks[i][j].get_int());
        }
        printf("\n");
    }
}

Memory::~Memory()
{

}