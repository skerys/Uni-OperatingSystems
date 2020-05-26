#pragma once

#include <memory>
#include <algorithm>

#include "ProcessClass.h"
#include "Kernel.h"

bool comparePriority(std::shared_ptr<Process> process1, std::shared_ptr<Process> process2)
{
    return (process1->get_priority() > process2->get_priority());
}

class ProcessPlanner
{
    std::shared_ptr<Kernel> kernel;

    void check_state_changes()
    {
    }

    void change_running_process()
    {
        std::shared_ptr<Process> current = kernel->runningProcess;

        //If current proccess is blocked move it to blocked process list
        if(current->get_state() == State::Blocked)
        {
            kernel->blockedProcesses.push_back(current);
        }

        //This process is the only one
        if(kernel->readyProcesses.size() == 0)
        {
            //This process will still run
            if(current->get_state() == State::Running)
            {
                //nothing happens this still runs
            }
            //or no process can run
            else
            {
                //special case, nothing can run
                fprintf(stderr, "No process can be set to Running, I am confused\n");
                exit(1);
            }
            
        }
        //There are more ready processes
        else
        {
            std::sort(kernel->readyProcesses.begin(), kernel->readyProcesses.end(), comparePriority);
            auto highestPrio = kernel->readyProcesses.front();

            //highest priority in readylist is higher than current priority
            if(highestPrio->get_priority() > current->get_priority())
            {
                current->set_state(State::Ready);
                kernel->readyProcesses.push_back(current);

                highestPrio->set_state(State::Running);
                kernel->runningProcess = highestPrio;
                kernel->readyProcesses.erase(kernel->readyProcesses.begin());
            }
            //highest priority in readylist is smaller than current priority
            else
            {
                //nothing happens this still runs
            }
        }

    }

};