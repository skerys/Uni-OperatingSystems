#pragma once

#include <vector>

#include "RealMachine.h"

class Process;
class Resource;

class Kernel
{
public:
    std::vector<std::shared_ptr<Process>>  allProcesses;
    std::vector<std::shared_ptr<Resource>> allResources;

    std::vector<std::shared_ptr<Process>> readyProcesses;
    std::vector<std::shared_ptr<Process>> blockedProcesses;

    std::shared_ptr<Process> runningProcess;

    std::shared_ptr<RealMachine> realMachine;

    void run_real_machine(RealMachine& realMachine)
    {
        realMachine.run_program("source.a");
    }
};