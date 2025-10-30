#pragma once

#include <memory>

namespace ECS
{

struct Entity;
class World;

struct IStash
{

    virtual ~IStash()                            = default;
    virtual void Remove(const Entity &entity)    = 0;
    virtual bool Has(const Entity &entity) const = 0;

    virtual void CloneTo(const Entity &source, std::shared_ptr<ECS::World> targetWorld, const Entity &targetEntity) = 0;
};

} // namespace ECS