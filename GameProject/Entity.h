#pragma once

#include "IComponent.h"
#include "iostream"
#include <memory>

using namespace Components;

namespace ECS
{
struct Entity
{
    Entity()
        : m_id(-1)
    {
    }
    Entity(long id)
        : m_id(id)
    {
    }
    ~Entity()
    {
        std::cout << ("Entity was destroyed. \n");
    }

  public:
    long m_id;
};

} // namespace ECS
