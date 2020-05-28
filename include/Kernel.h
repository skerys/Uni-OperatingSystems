#pragma once

#include <vector>

#include "RealMachine.h"
#include "ProcessClass.h"
#include "ProcessPlanner.h"

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

    ProcessPlanner      processPlanner;
    ResourceDistributor resourceDistributor;

    Kernel(RealMachine& _realMachine)
    {        
        realMachine = std::make_shared<RealMachine>(std::move(_realMachine));

        StartStop   startStop;
        startStop.execute();
    }

    void run_real_machine()
    {
        realMachine->run_program("source.a");
    }
};