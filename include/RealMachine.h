#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Register.h"
#include "Pager.h"
#include "VirtualMachine.h"

class RealMachine
{
private:
    VirtualMachine virtualMachines[VIRTUAL_MACHINE_NUM];
    Register ra, rb, rc;        // Bendro naudojimo registrai
    Register ptr;               // Puslapiu lenteles registras 
    Register ic;                // Komandu skaitiklis
    Flag sf;                    // Pozymio registras
    Flag mode;                  // Procesoriaus darbo rezimo registras 
    Flag pi, si, ti, oi;        // Pertraukimu (programinių, supervizorinių, taimerio, ivedimo/isvedimo) registrai
    Flag ca, cb, cc;            // Kanalu busenu registrai
    
    Pager   pager;
    bool    running;
public:
    RealMachine();

    void run()
    {
        load_registers(virtualMachines[0]);
        execute_command();
        if(interrupt_test())
        {
            change_mode();
            do_interrupt();
        }
        reduce_timer();
        write_registers(virtualMachines[0]);
    }

    void load_registers(VirtualMachine virtualMachines)
    {
        ra  = virtualMachines.ra;
        rb  = virtualMachines.rb;
        ic  = virtualMachines.ic;
        sf  = virtualMachines.sf;
        ptr = virtualMachines.ptr;
    }

    void execute_command()
    {

    }

    void change_mode()
    {

    }

    void do_interrupt()
    {

    }

    void reduce_timer()
    {

    }

    void write_registers(VirtualMachine virtualMachines)
    {
        virtualMachines.ra  = ra;
        virtualMachines.rb  = rb;
        virtualMachines.ic  = ic;
        virtualMachines.sf  = sf;
        virtualMachines.ptr = ptr;
    }

    bool interrupt_test()
    { 
        return ( (si.get_status() + pi.get_status() + oi.get_status() == 0) && ((ti.get_status() > 0) ? 0 : 1) ); 
    }

    ~RealMachine();
};