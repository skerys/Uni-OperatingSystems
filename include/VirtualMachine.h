#ifndef VM_H
#define VM_H

#include <iostream>
#include <memory>
#include <vector>

class VM
{
private:
    bool running;
    void execute();
public:
    VM();
    void loadMemory();
    void run();
    ~VM();
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