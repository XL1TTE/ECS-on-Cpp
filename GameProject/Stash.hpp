#pragma once

#include "Entity.h"
#include "IStash.h"
#include "Stash.h"
#include "World.h"
#include <memory>
#include <optional>

using namespace ECS;

template <typename T>
void Stash<T>::Add(const Entity &entity)
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

template <typename T>
void Stash<T>::Add(const Entity &entity, T &&component)
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

template <typename T>
void Stash<T>::Remove(const Entity &entity)
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

template <typename T>
T &Stash<T>::Get(const Entity &entity) const
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

template <typename T>
bool Stash<T>::Has(const Entity &entity) const
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
    return false;
}

template <typename T>
void Stash<T>::resize(size_t requiredSize)
{
    if (requiredSize <= m_capacity)
    {
        m_bufferSize = requiredSize;
        return;
    }

    std::cout << "STASH RESIZE: " << typeid(T).name() << " from " << m_capacity << " to " << requiredSize << std::endl;

    size_t newCapacity = m_capacity * 2;

    auto newBufferPtr = std::shared_ptr<std::optional<T>[]>(new std::optional<T>[newCapacity]);

    for (size_t i = 0; i < m_bufferSize; ++i)
    {
        newBufferPtr[i] = std::move(m_valuesPtr[i]);
    }

    m_valuesPtr  = std::move(newBufferPtr);
    m_bufferSize = requiredSize;
    m_capacity   = newCapacity;
}

template <typename T>
void Stash<T>::CloneTo(const Entity &source, std::shared_ptr<World> targetWorld, const Entity &targetEntity)
{
    static_assert(std::is_copy_constructible_v<T>, "Component type must be copy constructible for cloning");

    if (Has(source))
    {
        const T &sourceComponent = Get(source);

        auto targetStashWeak = targetWorld->GetStash<T>();
        auto targetStash     = targetStashWeak.lock();

        if (targetStash)
        {
            targetStash->Add(targetEntity, T(sourceComponent));
        }
    }
}