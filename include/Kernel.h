#pragma once

#include <vector>

#include "Collections.h"
#include "RealMachine.h"

class Kernel
{
    std::vector<Process> allProcesses;
    std::vector<Resource> allResources;

    std::vector<std::shared_ptr<Process>> readyProcesses;
    std::vector<std::shared_ptr<Process>> runningProcesses;

    std::shared_ptr<RealMachine> realMachine;
};