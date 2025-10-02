#pragma once

#include "IStash.h"

#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

namespace ECS
{

class World;

struct Entity;

struct FilterBuilder;

struct Filter
{
  public:
    using EntityList     = std::vector<std::shared_ptr<Entity>>;
    using iterator       = EntityList::iterator;
    using const_iterator = EntityList::const_iterator;

    explicit Filter(size_t builder_hash)
        : m_builderHash(builder_hash)
    {
    }

    ~Filter()
    {
        std::cout << "Filter was destroyed." << std::endl;
    }

    size_t m_builderHash;

  public:
    iterator begin()
    {
        return m_filteredEntities.begin();
    }
    iterator end()
    {
        return m_filteredEntities.end();
    }
    const_iterator begin() const
    {
        return m_filteredEntities.begin();
    }
    const_iterator end() const
    {
        return m_filteredEntities.end();
    }

    size_t size() const
    {
        return m_filteredEntities.size();
    }
    bool empty() const
    {
        return m_filteredEntities.empty();
    }

    const std::shared_ptr<Entity> &operator[](size_t index) const
    {
        return m_filteredEntities[index];
    }

  private:
    void UpdateEntities(EntityList &&entities)
    {
        m_filteredEntities = std::move(entities);
    }

  private:
    friend struct FilterBuilder;
    friend class World;

    Filter() = default;

    EntityList m_filteredEntities;
};

struct FilterBuilder : public std::enable_shared_from_this<FilterBuilder>
{
    ~FilterBuilder()
    {
        std::cout << "FilterBuilder was destroyed." << std::endl;
    }

  private:
    friend class World;

    explicit FilterBuilder(std::weak_ptr<World> world)
        : m_world(world), m_computedHash(-1)
    {
    }

    static std::shared_ptr<FilterBuilder> Create(std::weak_ptr<World> world)
    {
        return std::shared_ptr<FilterBuilder>(new FilterBuilder(world));
    }

  public:
    template <typename T>
    FilterBuilder &With();

    template <typename T>
    FilterBuilder &Without();

    std::weak_ptr<Filter> Build();

    void Commit()
    {
        if (m_filter)
        {
            UpdateFilter();
        }
    }

    bool Matches(const Entity &entity) const;

    size_t GetHash() const
    {
        size_t hash = 0;

        for (auto compHash : m_withComponents)
        {
            hash ^= compHash + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }

        for (auto compHash : m_withoutComponents)
        {
            hash ^= (~compHash) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }

        return hash;
    }

    void Dispose()
    {
        m_filter.reset();
    }

    bool IsDisposed() const
    {
        return m_filter == nullptr;
    }

  private:
    std::shared_ptr<Filter> &GetFilter()
    {
        return m_filter;
    }

    void UpdateFilter();

    std::weak_ptr<World>       m_world;
    std::shared_ptr<Filter>    m_filter;
    std::unordered_set<size_t> m_withComponents;
    std::unordered_set<size_t> m_withoutComponents;
    size_t                     m_computedHash = -1;
};

} // namespace ECS

#include "Filter.hpp"