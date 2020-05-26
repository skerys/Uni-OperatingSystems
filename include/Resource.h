#pragma once

#include <memory>
#include <vector>
#include <algorithm>

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

class Resource : public std::enable_shared_from_this<Resource>
{
private:
    int guid;                           // Globalus unikalus identifikatorius
    std::shared_ptr<Process> creator;

    ProcessList waitingProcesses;
    std::shared_ptr<Kernel> kernel;

    std::vector<std::shared_ptr<ResourceElement>> resourceElements;
public:
    Resource(Process& creatingProcess, Kernel& _kernel) //std::string resourceOuterName);
    {
        creator = std::make_shared<Process>(std::move(creatingProcess));
        kernel  = std::make_shared<Kernel>(std::move(_kernel));

        // Resursas pridedamas prie bendro resursų sąrašo
        kernel->allResources.push_back(shared_from_this());
        // Resursas pridedamas prie tėvo sukurtų resursų sąrašo
        creator->createdResources.resources.push_back(shared_from_this());
    // TODO: Sukuriamas resurso elementų sąrašas ???
        // Sukuriamas laukiančių procesų sąrašas (eil.28)
    }

    void request_resource(Process& callingProcess)
    {
    // Procesas, iškvietęs šį primityvą, yra užblokuojamas
        callingProcess.stop_process();
    // Procesas įtraukiamas į resurso laukiančių procesų sąrašą
        waitingProcesses.processes.push_back(callingProcess.shared_from_this());
    // TODO: Kvieciamas resurso paskirstytojas
        // resourceDistributor duoda visiems pizdy
    }

    void release_resource(ResourceElement& resourceElement)
    {
    // Resurso elementas, primityvui perduotas kaip funkcijos parametras, yra pridedamas prie resurso elementų sąrašo
        resourceElements.push_back(resourceElement.shared_from_this());
    // TODO: Šio primityvo pabaigoje yra kviečiamas resursų paskirstytojas
        // resourceDistributor duoda visiems pizdy
    }

    void delete_resource()
    {
    // KINDA_DONE_BUT_NOT_REALLY: Delete this from createdResources
        auto position = std::find(creator->createdResources.resources.begin(), creator->createdResources.resources.end(), shared_from_this());
        creator->createdResources.resources.erase(position);

        // Naikinamas jo elementų sąrašas, 
        resourceElements.clear();

        // Atblokuojami procesai, laukiantys šio resurso
        for(auto&& process : waitingProcesses.processes)
        {
            process->activate_process();
        }

    // TODO: išmetamas iš bendro resursų sąrašo,
        position = std::find(kernel->allResources.begin(), kernel->allResources.end(), shared_from_this());
        kernel->allResources.erase(position);
        // Panasisi kaip trinama ies createdResources, tik sikart is allResources
    }
};

class ResourceElement : public std::enable_shared_from_this<ResourceElement>
{

};