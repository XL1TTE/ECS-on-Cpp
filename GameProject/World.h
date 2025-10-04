#pragma once

#include <memory>
#include <unordered_map>

namespace ECS
{

struct Entity;

struct IStash;

template <typename T>
struct Stash;

struct FilterBuilder;
struct Filter;

class World final : public std::enable_shared_from_this<World>
{
  public:
    static std::shared_ptr<World> Create()
    {
        return std::shared_ptr<World>(new World());
    }

  public:
    ~World()
    {
        DisposeAllFilters();
    }
    World(const World &)            = delete;
    World &operator=(const World &) = delete;

  private:
    World() = default;

  private:
    std::unordered_map<size_t, std::shared_ptr<IStash>>        m_stashesMap;
    std::vector<std::shared_ptr<Entity>>                       m_disposedEntities;
    std::vector<std::shared_ptr<Entity>>                       m_entities;
    long                                                       m_nextEntityId = 0;
    std::unordered_map<size_t, std::shared_ptr<FilterBuilder>> m_cachedFilters;

  public:
    std::weak_ptr<Entity> CreateEntity();

    const std::vector<std::shared_ptr<Entity>> &GetAllEntities() const
    {
        return m_entities;
    }

    template <typename T>
    std::weak_ptr<Stash<T>> GetStash();

    void DisposeEntity(const Entity &entity);

    std::shared_ptr<FilterBuilder> Filter();

    void DisposeFilter(const std::shared_ptr<ECS::Filter> &filter);
    void DisposeFilter(const std::weak_ptr<ECS::Filter> &filter);

    void DisposeAllFilters();

    void CacheFilterBuilder(const std::shared_ptr<FilterBuilder> &builder);

    void Commit();

  private:
    std::weak_ptr<IStash> TryGetStash(size_t stash_hash) const;

  private:
    friend struct FilterBuilder;
    friend struct Filter;
};
} // namespace ECS

#include "World.hpp"
