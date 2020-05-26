#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "Collections.h"
#include "Kernel.h"

enum State { Blocked, BlockedStopped, Ready, ReadyStopped, Running };

class Process : public std::enable_shared_from_this<Process>
{
protected:
    State state;
    int priority;
    int guid;
    std::shared_ptr<Process> parent;
    std::vector<std::shared_ptr<Process>> children;
    std::vector<std::shared_ptr<Resource>> createdResources;

public:
    //TODO: Sukuriant jei norima perduoti kazkokius elementus
    Process(Process& _parent, State _startState, int _priority, Kernel& _kernel) : state(_startState), priority(_priority)
    {
        parent = std::make_shared<Process>(std::move(_parent));
        parent->children.push_back(shared_from_this());
        _kernel.allProcesses.push_back(shared_from_this());
        //TODO: suskaiciuoti guid
    }

    void destroy_process()
    {
        //Destroy all created resources
        for(auto&& res : createdResources)
        {
            //TODO: add resource destruction command
            //res.destroy_resource();
        }
        //Destroy all child processes
        for(auto&& child : children)
        {
            child->destroy_process();
        }
        //Remove this from parent's children list
        auto position = std::find(parent->children.begin(), parent->children.end(), shared_from_this());
        parent->children.erase(position);
        //Remove this from kernel process list
        //If needed remove this from ready resource list
    }

    void stop_process()
    {
        if(state == State::Running || state == State::Ready)
        {
            state = State::ReadyStopped;
        }
        else
        {
            state = State::BlockedStopped;
        }
    }

    void activate_process()
    {
        if(state == State::ReadyStopped)
        {
            state = State::Ready;
        }
        else
        {
            state = State::Blocked;
        }
        
    }

    void start();
    void stop();
    State getState();
};