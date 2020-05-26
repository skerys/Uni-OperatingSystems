#pragma once

#include <map>
#include <memory>

#include "Resource.h"

class ResourceDistributor
{
private:
    std::map<ResourceType, std::shared_ptr<Resource>> resources;
public:
    ResourceDistributor();
    void registerProcessForResource();
    void request_resource(ResourceType type);
    void releaseResource();
};