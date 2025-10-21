#pragma once
#include "IComponent.h"
#include <string>

namespace Components
{
struct Item : public IComponent
{
  public:
    explicit Item()
    {
    }
};
struct HiddenItem : public IComponent
{
  public:
    explicit HiddenItem()
    {
    }
};

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
struct Armor : public IComponent
{
  public:
    explicit Armor(short value)
        : m_Value(value)
    {
    }

  public:
    short m_Value;
};
struct Cost : public IComponent
{
  public:
    explicit Cost(float value)
        : m_Value(value)
    {
    }

  public:
    float m_Value;
};
struct Name : public IComponent
{
  public:
    explicit Name(std::string value)
        : m_Value(value)
    {
    }

  public:
    std::string m_Value;
};
struct Description : public IComponent
{
  public:
    explicit Description(std::string value)
        : m_Value(value)
    {
    }

  public:
    std::string m_Value;
};
struct Rarity : public IComponent
{
  public:
    enum Rarities : char
    {
        COMMON,
        UNCOMMON,
        RARE,
        EPIC,
        LEGENDARY
    };

  public:
    explicit Rarity(Rarities value)
        : m_Value(value)
    {
    }

  public:
    Rarities m_Value;
};
} // namespace Components