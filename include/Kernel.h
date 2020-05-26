#pragma once

#include <vector>

#include "RealMachine.h"

class Process;
class Resource;

class Kernel
{
public:
    std::vector<std::shared_ptr<Process>> allProcesses;
    std::vector<std::shared_ptr<Resource>> allResources;

    std::vector<std::shared_ptr<Process>> readyProcesses;
    std::vector<std::shared_ptr<Process>> runningProcesses;

    std::shared_ptr<RealMachine> realMachine;
};