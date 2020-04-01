#ifndef VM_H
#define VM_H

#include <iostream>
#include <memory>
#include <vector>
#include <cstdint>
#include "Memory.h"

class VM
{
private:
    bool running;
    void execute();

    uint8_t ptr; //registras nurodantis puslapiavimo lenteles adresa realioj atminty
    Memory tempMemory;

public:
    VM();
    ~VM();
    void loadMemory();



    void run();
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

#endif