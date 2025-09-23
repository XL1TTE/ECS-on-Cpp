#pragma once

#include "Entity.h"
#include "Stash.h"
#include <memory>
#include <unordered_map>

namespace ECS
{
class World final
{
  public:
    World()                         = default;
    ~World()                        = default;
    World(const World &)            = delete;
    World &operator=(const World &) = delete;

  private:
    std::unordered_map<size_t, std::shared_ptr<IStash>> m_stashesMap;
    std::vector<std::shared_ptr<Entity>>                m_disposedEntities;
    std::vector<std::shared_ptr<Entity>>                m_entities;
    size_t                                              m_nextEntityId = 0;

  public:
    std::weak_ptr<Entity> CreateEntity()
    {
        auto entity = std::make_shared<Entity>(m_nextEntityId);
        m_nextEntityId++;
        m_entities.push_back(entity);
        return entity;
    }

    template <typename T>
    std::weak_ptr<Stash<T>> GetStash()
    {
        static_assert(std::is_base_of_v<IComponent, std::decay_t<T>>,
                      "T must derive from IComponent");

        size_t stashHash = typeid(T).hash_code();

        auto it = m_stashesMap.find(stashHash);
        if (it == m_stashesMap.end())
        {
            auto stash              = std::make_shared<Stash<T>>();
            m_stashesMap[stashHash] = stash;
            return stash;
        }

        return std::static_pointer_cast<Stash<T>>(it->second);
    }

    void DisposeEntity(const Entity &entity)
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
            std::remove(m_entities.begin(), m_entities.end(), disposed);
            m_disposedEntities.push_back(disposed);
        }
    }
};
} // namespace ECS