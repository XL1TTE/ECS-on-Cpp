#pragma once

#include "IComponent.h"
#include "World.h"

using namespace ECS;

template <typename T>
std::weak_ptr<Stash<T>> World::GetStash()
{
    static_assert(std::is_base_of_v<Components::IComponent, std::decay_t<T>>,
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
