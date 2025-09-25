#pragma once

#include "Entity.h"

namespace ECS
{
struct IStash
{

    virtual ~IStash()                            = default;
    virtual void Remove(const Entity &entity)    = 0;
    virtual bool Has(const Entity &entity) const = 0;
};

} // namespace ECS