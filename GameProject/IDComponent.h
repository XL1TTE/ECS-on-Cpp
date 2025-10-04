#pragma once
#include "IComponent.h"

#include <string>

namespace Components
{
struct IDComponent : public IComponent
{
  public:
    IDComponent()
        : m_id("")
    {
    }
    explicit IDComponent(std::string &&id)
        : m_id(id)
    {
    }

  public:
    std::string m_id;
};
} // namespace Components