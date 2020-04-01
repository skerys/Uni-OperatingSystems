#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Memory.h"
#include "Register.h"

class VirtualMachine
{
private:
    Memory memory;
    Register ra, rb;
    Register ic;
    Flag sf;
    bool running;
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
