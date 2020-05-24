#pragma once

#include <vector>
#include <memory>

#include "Kernel.h"
#include "Process.h"
#include "Resource.h"

class ProcessList{
public:
    std::vector<std::shared_ptr<Process>> processes;
    std::shared_ptr<Kernel> kernel;

};

class ResourceList{
public:
    std::vector<std::shared_ptr<Resource>> resources;
    std::shared_ptr<Kernel> kernel;
};