#include <stdio.h>
#include "Memory.h"

Memory::Memory()
{

}

void Memory::print()
{
    for(int i = 0; i < MEMORY_BLOCK_COUNT; ++i)
    {
        printf("%X: ", i);
        for(int j = 0; j < BLOCK_LENGTH; ++j){
            printf("%X ", blocks[i][j]);
        }
        printf("\n");
    }
}

Memory::~Memory()
{

}