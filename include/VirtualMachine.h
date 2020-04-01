#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Memory.h"

class VirtualMachine
{
private:
    Memory memory;
    bool running;
    void execute();
public:
    VirtualMachine();
    void loadMemory();
    void run();
    ~VirtualMachine();
};

enum CommandCode
{
    WAxy,
    WBxy,
    LAxy,
    LBxy,
    ADDX,
    SUBX,
    MULX,
    DIVX,
    CMPX,
    JPxy,
    JExy,
    JNxy,
    JGxy,
    INxy,
    INBx,
    OTxy,
    OTBx,
    FOxy,
    FCLS,
    FDEL,
    FWxy,
    FWBx,
    FRxy,
    FRBx,
    HALT
};