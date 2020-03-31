#ifndef REALMACHINE_H
#define REALMACHINE_H

#include <iostream>
#include <memory>
#include <vector>

#include "VirtualMachine.h"

class RealMachine
{
private:
    VirtualMachine audine, bemsas, multipla, chuliganke;
public:
    RealMachine();
    ~RealMachine();
};

#endif
