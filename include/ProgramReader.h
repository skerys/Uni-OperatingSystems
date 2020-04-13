#pragma once

#include <fstream>

#include "Memory.h"

class ProgramReader
{
private:
    Memory& memory;

    std::ifstream file;
public:
    ProgramReader(Memory& _memory) : memory(_memory) {}
    void set_memory(std::string filename);
    char set_digit(char symbol);
    std::string set_datablock();
    void set_codeblock(std::string line);
    void reading_error(const char *message);
    Memory& get_memory();
};
