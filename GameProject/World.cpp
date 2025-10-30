
#pragma once

#include "World.h"
#include "Entity.h"
#include "Filter.h"
#include "IComponent.h"
#include "IStash.h"
#include "Stash.h"
#include <memory>
#include <unordered_map>

using namespace ECS;

std::weak_ptr<Entity> World::CreateEntity()
{
    auto entity = std::make_shared<Entity>(m_nextEntityId);
    m_nextEntityId++;
    m_entities.push_back(entity);
    return entity;
}

std::weak_ptr<Entity> World::CloneTo(const Entity &source, std::shared_ptr<World> targetWorld)
{
    auto newEntityWeak = targetWorld->CreateEntity();
    auto newEntity     = newEntityWeak.lock();

    if (!newEntity)
    {
        return {};
    }

    for (const auto &[stashHash, stash] : m_stashesMap)
    {
        if (stash->Has(source))
        {
            stash->CloneTo(source, targetWorld, *newEntity);
        }
    }

    return newEntityWeak;
}

void World::DisposeEntity(const Entity &entity)
{
    if (entity.m_id <= -1)
    {
        return;
    }
    for (auto pair : m_stashesMap)
    {
        pair.second->Remove(entity); // remove entity from every stash
    }

    std::shared_ptr<Entity> disposed;
    for (auto e : m_entities)
    {
        if (e->m_id == entity.m_id)
        {
            disposed = e;
            break;
        }
    }
    if (disposed != nullptr)
    {
        std::erase(m_entities, disposed);
        m_disposedEntities.push_back(disposed);
    }
}

/// <summary>
///
/// </summary>
/// <param name="stash_hash"></param>
/// <returns>Returns expired weak ptr if not sutable stash was found.</returns>
std::weak_ptr<IStash> World::TryGetStash(size_t stash_hash) const
{
    auto it = m_stashesMap.find(stash_hash);
    if (it == m_stashesMap.end())
    {
        return std::weak_ptr<IStash>();
    }

    return std::static_pointer_cast<IStash>(it->second);
}

std::shared_ptr<FilterBuilder> World::Filter()
{
    if (shared_from_this() == nullptr)
    {
        throw std::bad_weak_ptr();
    }
    return FilterBuilder::Create(shared_from_this());
}

void World::Commit()
{
    for (auto it = m_cachedFilters.begin(); it != m_cachedFilters.end();)
    {
        (it->second)->Commit();
        ++it;
    }
}

void World::DisposeFilter(const std::shared_ptr<ECS::Filter> &filter)
{
    for (auto pair : m_cachedFilters)
    {
        if (pair.first == filter->m_builderHash)
        {
            m_cachedFilters.erase(pair.first);
            pair.second->Dispose();
        }
    }
}
void World::DisposeFilter(const std::weak_ptr<ECS::Filter> &filter)
{
    auto f = filter.lock();
    for (auto pair : m_cachedFilters)
    {
        if (pair.first == f->m_builderHash)
        {
            m_cachedFilters.erase(pair.first);
            pair.second->Dispose();
            return;
        }
    }
}

void World::DisposeAllFilters()
{
    for (auto pair : m_cachedFilters)
    {
        pair.second->Dispose();
    }
    m_cachedFilters.clear();
}

void World::CacheFilterBuilder(const std::shared_ptr<FilterBuilder> &builder)
{
    size_t hash           = builder->GetHash();
    m_cachedFilters[hash] = builder;
}
