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
    explicit IDComponent(long &&id)
        : m_id(id)
    {
    }

  private:
    long m_id;

  public:
    const long &getId() const
    {
        return m_id;
    }
    void setId(long id)
    {
        m_id = id;
    }
};
} // namespace Components