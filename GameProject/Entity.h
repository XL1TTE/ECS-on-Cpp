#pragma once

#include "IComponent.h"
#include "iostream"
#include <memory>

using namespace Components;

struct Entity
{
    Entity()
        : m_id(-1)
    {
    }
    Entity(long id)
        : m_id(id)
    {
    }
    ~Entity()
    {
        std::cout << ("Entity was destroyed. \n");
    }

  public:
    long m_id;

  private:
    static const size_t         m_bufferSize               = 64;
    std::shared_ptr<IComponent> m_components[m_bufferSize] = {nullptr};

  public:
    template <typename T>
    void AddComponent(const T &&component)
    {
        static_assert(std::is_base_of_v<IComponent, std::decay_t<T>>,
                      "T must derive from IComponent");

        for (int i = 0; i < m_bufferSize; ++i)
        {
            if (m_components[i] == nullptr)
            {
                m_components[i] = std::make_shared<std::decay_t<T>>(component);
                break;
            }
        }
    }
    void AddComponent(const std::shared_ptr<IComponent> component)
    {
        for (int i = 0; i < m_bufferSize; ++i)
        {
            if (m_components[i] == nullptr)
            {
                m_components[i] = component;
                break;
            }
        }
    }

    template <typename T>
    std::shared_ptr<T> GetComponent() const
    {
        for (int i = 0; i < m_bufferSize; ++i)
        {
            if (m_components[i] != nullptr)
            {
                auto component = std::dynamic_pointer_cast<T>(m_components[i]);
                if (component != nullptr)
                {
                    return component;
                }
            }
        }
        return nullptr;
    }
};
