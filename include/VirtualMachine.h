#pragma once

#include <iostream>
#include <memory>
#include <vector>
#if _WIN32 || _WIN64
#include <sys\stat.h>
#endif

#include "Memory.h"
#include "Register.h"


enum RegisterType { RA, RB };
enum ArithmeticCommand { ADD, SUB, MUL, DIV };
enum JumpType { ALWAYS, IF_EQUAL, IF_NOT_EQUAL, IF_GREATER };

class VirtualMachine
{
private:
    bool    running;
    void do_debug();
    
public:
    Register ra, rb;            // Bendro naudojimo registrai
    Register ic;                // Komandu skaitiklis
    Register ptr;               // Puslapiavimo lenteles blokas realioje atmintyje
    Flag     sf;                // Pozymio registras

    VirtualMachine()
    {
        running = true;
    }

    //TODO: Remove this
    void run();    
    //-----
    void set_ptr(Word word);
    ~VirtualMachine();
};