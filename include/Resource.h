#pragma once
#include <memory>

#include "Process.h"
#include "Collections.h"

class Resource
{
    int guid;
    std::shared_ptr<Process> creator;

    ProcessList waitingProcesses;
    std::shared_ptr<Kernel> kernel;
};