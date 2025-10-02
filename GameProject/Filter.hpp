#pragma once

#include "IComponent.h"

using namespace ECS;

template <typename T>
FilterBuilder &FilterBuilder::With()
{
    static_assert(std::is_base_of_v<Components::IComponent, std::decay_t<T>>,
                  "T must derive from IComponent");
    m_withComponents.insert(typeid(T).hash_code());
    return *this;
}

template <typename T>
FilterBuilder &FilterBuilder::Without()
{
    static_assert(std::is_base_of_v<Components::IComponent, std::decay_t<T>>,
                  "T must derive from IComponent");
    m_withoutComponents.insert(typeid(T).hash_code());
    return *this;
}