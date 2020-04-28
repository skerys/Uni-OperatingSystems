#pragma once

#include <fstream>

#include "Memory.h"
#include "Pager.h"

class ProgramReader
{
private:
    Memory& memory;
    Pager&  pager;
    Word ptr;
    std::ifstream file;
public:
    ProgramReader(Memory& _memory, Pager& _pager, Word ptr) : memory(_memory), pager(_pager)
    {
        this->ptr = ptr;
    }
    int set_memory(std::string filename);
    char set_digit(char symbol);
    std::string set_datablock();
    int set_codeblock(std::string line);
    void reading_error(const char *message);
    Memory& get_memory();
};
