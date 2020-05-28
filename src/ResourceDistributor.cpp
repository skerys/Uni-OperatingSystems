#include "ResourceDistributor.h"

ResourceDistributor::ResourceDistributor()
{
    this->resources.insert(std::make_pair(ResourceType::MOSEnd,                 std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::ProgramFileInMemory,    std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::ProgramInMemory,        std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::ProgramInUserMemory,    std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::FromInterrupt,          std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::Interrupt,              std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::FileCommandRequest,     std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::FileCommandDone,        std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::PrintDataRequest,       std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::PrintDataDone,          std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::Interrupt,              std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::ReadDataRequest,        std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::ReadDataDone,           std::make_shared<Resource>()));
    this->resources.insert(std::make_pair(ResourceType::Null,                   std::make_shared<Resource>()));
}

void ResourceDistributor::register_process_for_resource()
{

}

void ResourceDistributor::release_resource()
{

}