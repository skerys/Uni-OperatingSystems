#pragma once
#include <memory>

#include "Process.h"
#include "Collections.h"

enum ResourceType { MOSEnd,
                    ProgramFileInMemory, 
                    ProgramInMemory, 
                    ProgramInUserMemory, 
                    FromInterrupt, 
                    Interrupt,
                    FileCommandRequest,
                    FileCommandDone,
                    PrintDataRequest,
                    PrintDataDone,
                    ReadDataRequest,
                    ReadDataDone,
                    Null };


class Resource
{
private:
    int guid;                           // Globalus unikalus identifikatorius
    std::shared_ptr<Process> creator;

    ProcessList waitingProcesses;
    std::shared_ptr<Kernel> kernel;
public:
    Resource(Process& creatingProcess, Kernel& _kernel) //std::string resourceOuterName);
    {
        creator = std::make_shared<Process>(std::move(creatingProcess));
        kernel  = std::make_shared<Kernel>(std::move(_kernel));

        kernel->allResources.push_back(this);
    }

    void request_resource()
    {}

    void release_resource()
    {}

    void delete_resource()
    {}
};