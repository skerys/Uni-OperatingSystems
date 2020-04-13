#include "../include/Pager.h"

int Pager::get_real_addr(int virtual_addr, Word ptr)
{
    //Virtual address is xy
    int x = virtual_addr / 16;
    int y = virtual_addr % 16;

    //PTR register is ??uv
    int u = ptr[2];
    int v = ptr[3];

    int ptrAddr = 16*u + v;

    int xBlockReal = 16 * memoryRef[ptrAddr][x].get_int();
    int xyReal = xBlockReal + y;

    return xyReal;
}

void Pager::setup_vm_paging(VirtualMachine vm, int index)
{
    Block ptrBlock;
    int realBlock = index;

    for(int i = 0; i < BLOCK_LENGTH; ++i)
    {
        ptrBlock[i] = realBlock;
        realBlock += VIRTUAL_MACHINE_NUM;
    }

    memoryRef[realBlock] = ptrBlock;

    Word ptrWord;
    ptrWord.set_bytes(0,0, realBlock / 16, realBlock % 16);

    vm.set_ptr(ptrWord);
}