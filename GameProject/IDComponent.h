#pragma once
#include "IComponent.h"

namespace Components
{
struct IDComponent : public IComponent
{
  public:
    IDComponent()
        : m_id(-1)
    {
    }
    explicit IDComponent(size_t &&id)
        : m_id(id)
    {
    }

  public:
    size_t m_id;
};
} // namespace Components