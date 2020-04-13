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


    void run()
    {
        //with one VM
        // load_registers(vm);
        // execute_command();
        // if(interrupt_test())
        // {
        //     change_mode();
        //     do_interrupt();
        // }
        // reduce_timer();
        // write_registers(vm);

    }

    ~RealMachine();
};