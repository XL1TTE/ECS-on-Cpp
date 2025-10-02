#pragma once

#include "IStash.h"
#include <memory>
#include <optional>

namespace ECS
{

struct Entity;

template <typename T>
struct Stash : public IStash
{
    Stash()
        : m_bufferSize(16), m_capacity(16)
    {
        m_valuesPtr = std::shared_ptr<std::optional<T>[]>(new std::optional<T>[m_capacity]);
    }

    Stash(Stash &&other) noexcept
        : m_bufferSize(other.m_bufferSize), m_capacity(other.m_capacity), m_valuesPtr(std::move(other.m_valuesPtr))
    {
        other.m_bufferSize = 0;
        other.m_capacity   = 0;
        other.m_valuesPtr  = nullptr;
    }

    Stash &operator=(Stash &&other) noexcept
    {
        if (this != &other)
        {
            m_bufferSize = other.m_bufferSize;
            m_capacity   = other.m_capacity;
            m_valuesPtr  = std::move(other.m_valuesPtr);

            other.m_bufferSize = 0;
            other.m_capacity   = 0;
            other.m_valuesPtr  = nullptr;
        }
        return *this;
    }

  private:
    size_t                              m_bufferSize = 0;
    size_t                              m_capacity   = 0;
    std::shared_ptr<std::optional<T>[]> m_valuesPtr;

  public:
    void Add(const Entity &entity);

    void Add(const Entity &entity, T &&component);

    void Remove(const Entity &entity) override;

    T &Get(const Entity &entity) const;

    bool Has(const Entity &entity) const override;

  private:
    void resize(size_t requiredSize);
};
} // namespace ECS

#include "Stash.hpp"