#pragma once

#include <vector>
#include <memory>

class Process;
class Kernel;
class Resource;

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