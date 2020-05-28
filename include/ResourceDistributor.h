#pragma once

#include <map>
#include <memory>
#include <queue>

#include "Resource.h"

class ResourceDistributor
{
private:
    std::map<ResourceType, std::shared_ptr<Resource>> resources;

    std::map<ResourceType, std::queue<std::shared_ptr<Process>>> waitingList;
public:
    ResourceDistributor();
    void registerProcessForResource();
    void request_resource(ResourceType type);
    void releaseResource();
};