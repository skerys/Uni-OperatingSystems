#pragma once

#include <memory>
#include <vector>
#include <map>
#include <algorithm>

#include "ProcessClass.h"
#include "Collections.h"
#include "Kernel.h"

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

class ResourceElement : public std::enable_shared_from_this<ResourceElement>
{

};

class Resource : public std::enable_shared_from_this<Resource>
{
private:
    ResourceType type;                                  // Resuro tipas
    std::shared_ptr<Kernel>  kernel;                            // Nuoroda i branduoli
    std::shared_ptr<Process> creator;                           // Nuoroda i kureja
    std::shared_ptr<ResourceDistributor> distributor;
    int guid;                                                   // Globalus unikalus identifikatorius
    ProcessList waitingProcesses;                               // Resurso laukianciu procesu sarasas
    std::map<std::string, ResourceElement> elements;    // Resurso elementu sarasas
    
public:
    Resource(ResourceType _type, Kernel& _kernel, Process& creatingProcess, ResourceDistributor& resourceDistributor)
    {
        kernel      = std::make_shared<Kernel>(std::move(_kernel));
        creator     = std::make_shared<Process>(std::move(creatingProcess));
        distributor = std::make_shared<ResourceDistributor>(std::move(resourceDistributor));

        type = _type;
        // Resursas pridedamas prie bendro resursų sąrašo
        kernel->allResources.insert({type, shared_from_this()});
        // Resursas pridedamas prie tėvo sukurtų resursų sąrašo
        creator->createdResources.resources.push_back(shared_from_this());
        // Sukuriamas laukiančių procesų sąrašas - waitingProcesses
    }

    Resource(ResourceType _type, Kernel& _kernel, Process& creatingProcess, ResourceDistributor& resourceDistributor, std::map<std::string, ResourceElement> resourceElements)
    {
        kernel      = std::make_shared<Kernel>(std::move(_kernel));
        creator     = std::make_shared<Process>(std::move(creatingProcess));
        distributor = std::make_shared<ResourceDistributor>(std::move(resourceDistributor));
        // TODO: Sukuriamas resurso elementų sąrašas ???
        elements    = resourceElements;

        type = _type;
        // Resursas pridedamas prie bendro resursų sąrašo
        kernel->allResources.insert({type, shared_from_this()});
        // Resursas pridedamas prie tėvo sukurtų resursų sąrašo
        creator->createdResources.resources.push_back(shared_from_this());
        // Sukuriamas laukiančių procesų sąrašas - waitingProcesses
    }

    void request_resource(Process& callingProcess)
    {
        callingProcess.set_state(State::Blocked);
        // Procesas įtraukiamas į resurso laukiančių procesų sąrašą
<<<<<<< HEAD
        waitingProcesses.processes.push_back(callingProcess.shared_from_this());
        // Resurso paskirstytojas
        kernel->resourceDistributor.execute();
=======
        waitingProcesses.processes.push_back(std::make_shared<Process>(std::move(callingProcess)));
        callingProcess.set_state(State::Blocked);

        
    // TODO: Kvieciamas resurso paskirstytojas
        // distributor.execute() or smth
>>>>>>> 17a98470c0ed6064cac4fc07c76eaf3b3ed068e2
    }

    void release_resource(ResourceElement& resourceElement)
    {
        // Resurso elementas, primityvui perduotas kaip funkcijos parametras, yra pridedamas prie resurso elementų sąrašo
        elements.insert( {"resource element", resourceElement} );
        // Resurso paskirstytojas
            kernel->resourceDistributor.execute();
    }

    void delete_resource()
    {
        auto position = std::find(creator->createdResources.resources.begin(), creator->createdResources.resources.end(), shared_from_this());
        creator->createdResources.resources.erase(position);

        // Naikinamas jo elementų sąrašas 
        elements.clear();

        // Atblokuojami procesai, laukiantys šio resurso
        for(auto&& process : waitingProcesses.processes)
        {
            process->activate_process();
        }

        // Išmetamas iš bendro resursų sąrašo,
        position = std::find(kernel->allResources.begin(), kernel->allResources.end(), shared_from_this());
        kernel->allResources.erase(position);
    }
};

class ResourceElement
{
private:
    int         int_value;
    std::string str_value;
public:
    void set_int_value(int _value)
    {
        int_value = _value;
    }
    void set_str_value(std::string _value)
    {
        str_value = _value;
    }

    int get_int_value()
    {
        return int_value;
    }
    std::string get_str_value()
    {
        return str_value;
    }
};
