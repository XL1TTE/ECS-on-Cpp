#pragma once
#include "IComponent.h"

namespace Components
{
struct Damage : public IComponent
{
  public:
    explicit Damage(short value)
        : m_Value(value)
    {
    }

  public:
    short m_Value;
};
} // namespace Components