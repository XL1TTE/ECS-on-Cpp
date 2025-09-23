#pragma once

namespace Components
{
struct IComponent
{
  public:
    IComponent()          = default;
    virtual ~IComponent() = default;
};
}; // namespace Components
