#include "Filter.h"
#include "World.h"
#include <memory>
#include <stdexcept>

using namespace ECS;

std::weak_ptr<Filter> FilterBuilder::Build()
{
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
}

bool FilterBuilder::Matches(const Entity &entity) const
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

void FilterBuilder::UpdateFilter()
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