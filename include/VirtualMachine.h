#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <sys\stat.h>

#include "Memory.h"
#include "Register.h"


enum RegisterType { RA, RB };
enum ArithmeticCommand { ADD, SUB, MUL, DIV };
enum JumpType { ALWAYS, IF_EQUAL, IF_NOT_EQUAL, IF_GREATER };

class VirtualMachine
{
private:
    Memory& memory;
    bool    running;
    void do_debug();
    
public:
    Register ra, rb;            // Bendro naudojimo registrai
    Register ic;                // Komandu skaitiklis
    Register ptr;               // Puslapiavimo lenteles blokas realioje atmintyje
    Flag     sf;                // Pozymio registras

    VirtualMachine(Memory& _memory) : memory(_memory)
    {
        running = true;
    }

    //TODO: Remove this
    void loadMemory(Memory& _memory);
    void run();    
    //-----
    void set_ptr(Word word);
    ~VirtualMachine();
};