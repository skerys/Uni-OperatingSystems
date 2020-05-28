#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "Kernel.h"
#include "Collections.h"

enum State { Blocked, 
             BlockedStopped, 
             Ready, 
             ReadyStopped, 
             Running };

class Process : public std::enable_shared_from_this<Process>
{
protected:
    State state;
    int priority;
    std::shared_ptr<Process> parent;
    std::shared_ptr<Kernel>  kernel;

    ProcessList children;
public:
    ResourceList createdResources;

    // Perduodama nuoroda į tėvą; pradinė būsena; prioritetas
    Process(Process& _parent, State _startState, int _priority, Kernel& _kernel) : state(_startState), priority(_priority)
    {
        parent = std::make_shared<Process>(std::move(_parent));
        kernel = std::make_shared<Kernel>(std::move(_kernel));
        // Registruojamas tėvo-sūnų sąraše
        parent->children.processes.push_back(shared_from_this());
        // Registruojamas bendrame procesų sąraše
        kernel->allProcesses.push_back(shared_from_this());
        // Visu primityvu pabaigoje kvieciamas procesu planuotojas
        kernel->processPlanner.execute();
    }

    void destroy_process()
    {
        // Sukurtų resursų naikinimas
        for (auto&& resource : createdResources.resources)
        {
            resource->delete_resource();
        }
        // Vaikų naikinimas
        for (auto&& child : children.processes)
        {
            child->destroy_process();
        }
        // Išmetamas iš tėvo sukurtų procesų sąrašo. 
        auto position = std::find(parent->children.processes.begin(), parent->children.processes.end(), shared_from_this());
        parent->children.processes.erase(position);
        // Visu primityvu pabaigoje kvieciamas procesu planuotojas
        kernel->processPlanner.execute();
    }

    void stop_process()
    {
        if(state == State::Running)
        {
            state = State::ReadyStopped;
        }
        else if(state == State::Ready)
        {
            state = State::ReadyStopped;

            //remove the stopped process from ready processes list
            auto position = std::find(kernel->readyProcesses.begin(), kernel->readyProcesses.end(), shared_from_this());
            kernel->readyProcesses.erase(position);
        }
        else
        {
            state = State::BlockedStopped;
        }
        // Visu primityvu pabaigoje kvieciamas procesu planuotojas
        kernel->processPlanner.execute();
    }

    void activate_process()
    {
        if(state == State::ReadyStopped)
        {
            state = State::Ready;
            
            kernel->readyProcesses.push_back(shared_from_this());
        }
        else
        {
            state = State::Blocked;
        }
        // Visu primityvu pabaigoje kvieciamas procesu planuotojas
        kernel->processPlanner.execute();
    }

    void start();
    void stop();
    State get_state();
    void set_state(State newState);

    int get_priority();
};

class StartStop 
{
private:
    bool processesCreated;

public:
    void execute()
    {

    }

    void create_all()
    {

    }

    void delete_all()
    {

    }
};