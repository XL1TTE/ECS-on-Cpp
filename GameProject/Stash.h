#pragma once

#include "Entity.h"
#include <memory>
#include <optional>

namespace ECS
{
struct IStash
{

    virtual ~IStash()                            = default;
    virtual void Remove(const Entity &entity)    = 0;
    virtual bool Has(const Entity &entity) const = 0;
};

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
    void Add(const Entity &entity)
    {
        if (entity.m_id <= -1)
        {
            throw std::exception("You are trying to add component to a dispossed/null entity.");
        }

        if (entity.m_id + 1 >= m_bufferSize)
        {
            resize(entity.m_id + 1);
        }

        m_valuesPtr[entity.m_id] = T{};
    }
    void Add(const Entity &entity, T &&component)
    {
        if (entity.m_id <= -1)
        {
            throw std::exception("You are trying to add component to a dispossed/null entity.");
        }

        if (entity.m_id + 1 >= m_bufferSize)
        {
            resize(entity.m_id + 1);
        }

        m_valuesPtr[entity.m_id] = std::move(component);
    }

    void Remove(const Entity &entity) override
    {
        if (entity.m_id <= -1)
        {
            throw std::exception("You are trying to remove component from dispossed/null entity.");
        }
        if (entity.m_id + 1 > m_bufferSize)
        {
            return;
        }

        m_valuesPtr[entity.m_id] = std::nullopt;
    }

    T &Get(const Entity &entity) const
    {
        if (entity.m_id <= -1)
        {
            throw std::exception("You are trying to get component from dispossed/null entity.");
        }

        if (!Has(entity))
        {
            throw std::exception("Entity not exist in this stash. Use Has method before.");
        }

        return m_valuesPtr[entity.m_id].value();
    }

    bool Has(const Entity &entity) const override
    {
        if (entity.m_id <= -1)
        {
            return false;
        }
        if (entity.m_id + 1 > m_bufferSize)
        {
            return false;
        }
        if (m_valuesPtr[entity.m_id].has_value())
        {
            return true;
        }
    }

  private:
    void resize(size_t requiredSize)
    {
        if (requiredSize <= m_capacity)
        {
            m_bufferSize = requiredSize;
            return;
        }
        size_t newCapacity  = m_capacity * 2;
        auto   newBufferPtr = std::shared_ptr<std::optional<T>[]>(new std::optional<T>[newCapacity]);

        for (size_t i = 0; i < m_bufferSize; ++i)
        {
            newBufferPtr[i] = std::move(m_valuesPtr[i]);
        }

        m_valuesPtr  = std::move(newBufferPtr);
        m_bufferSize = requiredSize;
        m_capacity   = newCapacity;
    }
};
} // namespace ECS