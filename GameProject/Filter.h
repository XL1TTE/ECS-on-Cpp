#pragma once

#include "Entity.h"
#include "World.h"
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_set>
#include <vector>

namespace ECS
{

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
        std::cout << "Destructor of Filter. \n";
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
        std::cout << "Destructor of Filter Builder. \n";
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
    FilterBuilder &With()
    {
        static_assert(std::is_base_of_v<IComponent, std::decay_t<T>>,
                      "T must derive from IComponent");
        m_withComponents.insert(typeid(T).hash_code());
        return *this;
    }

    template <typename T>
    FilterBuilder &Without()
    {
        static_assert(std::is_base_of_v<IComponent, std::decay_t<T>>,
                      "T must derive from IComponent");
        m_withoutComponents.insert(typeid(T).hash_code());
        return *this;
    }

    std::weak_ptr<Filter> Build()
    {
        if (m_world.expired())
        {
            throw std::runtime_error("World is expired");
        }

        m_computedHash = GetHash();

        if (auto world = m_world.lock())
        {
            if (world->m_cachedFilters.contains(m_computedHash))
            {
                m_filter = world->m_cachedFilters[m_computedHash]->GetFilter();
                return m_filter;
            }

            auto filter = std::make_shared<Filter>(m_computedHash);
            m_filter    = filter;
            UpdateFilter();
            world->CacheFilterBuilder(shared_from_this());

            return filter;
        }
        return std::weak_ptr<Filter>();
    }

    void Commit()
    {
        if (m_filter)
        {
            UpdateFilter();
        }
    }

    bool Matches(const Entity &entity) const
    {
        if (auto world = m_world.lock())
        {
            // With filter
            for (auto componentHash : m_withComponents)
            {
                auto stash = world->TryGetStash(componentHash);
                if (stash.expired())
                {
                    return false;
                }
                if (stash.lock()->Has(entity) == false)
                {
                    return false;
                }
            }

            // Проверка Without компонентов
            for (auto componentHash : m_withoutComponents)
            {
                auto stash = world->TryGetStash(componentHash);
                if (stash.expired() == false)
                {
                    if (stash.lock()->Has(entity))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

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

    void UpdateFilter()
    {
        if (auto world = m_world.lock())
        {
            auto               entities = world->GetAllEntities();
            Filter::EntityList filteredEntities;

            for (const auto entity : entities)
            {
                if (Matches(*entity))
                {
                    filteredEntities.push_back(entity);
                }
            }

            m_filter->UpdateEntities(std::move(filteredEntities));
        }
    }

    std::weak_ptr<World>       m_world;
    std::shared_ptr<Filter>    m_filter;
    std::unordered_set<size_t> m_withComponents;
    std::unordered_set<size_t> m_withoutComponents;
    size_t                     m_computedHash = -1;
};

} // namespace ECS