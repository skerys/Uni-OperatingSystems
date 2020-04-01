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
    Register ra, rb, rc;
    Register ptr;
    Register ic;
    Flag sf, mode, pi, si, ti, oi, ca, cb, cc;
public:
    RealMachine();
    ~RealMachine();
};