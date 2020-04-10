#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Register.h"
#include "VirtualMachine.h"

#define VIRTUAL_MACHINE_NUM 4

class RealMachine
{
private:
    //VirtualMachine virtualMachines[VIRTUAL_MACHINE_NUM];
    Register ra, rb, rc;        // Bendro naudojimo registrai
    Register ptr;               // Puslapiu lenteles registras 
    Register ic;                // Komandu skaitiklis
    Flag sf;                    // Pozymio registras
    Flag mode;                  // Procesoriaus darbo rezimo registras 
    Flag pi, si, ti, oi;        // Pertraukimu (programinių, supervizorinių, taimerio, ivedimo/isvedimo) registrai
    Flag ca, cb, cc;            // Kanalu busenu registrai
public:
    RealMachine();
    //void interrupt_test(){ return​ si + pi + oi == ​0​ ​AND​ ti > ​0​ ? ​0​ : 1; } 
    ~RealMachine();
};