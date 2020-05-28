#pragma once

#include <map>
#include <memory>
#include <queue>

#include "Resource.h"

class ResourceDistributor
{
private:
    std::map<ResourceType, std::shared_ptr<Resource>> resources;
    std::map<ResourceType, std::queue<Process>> waitingProcesses;
public:
    ResourceDistributor();
    void register_process_for_resource();
    void request_resource(ResourceType type);
    void release_resource();
};