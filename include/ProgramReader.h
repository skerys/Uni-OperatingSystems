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
    void setMemory(std::string filename);
    char setDigit(char symbol);
    std::string setDataBlock();
    void setCodeBlock(std::string line);
    void readingError(const char *message);
    Memory& getMemory();
};
