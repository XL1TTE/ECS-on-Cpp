#pragma once

#include "DataBase.h"
#include "Entity.h"
#include "IComponent.h"
#include "Stash.h"
#include "World.h"
#include <memory>
#include <optional>

using namespace DB;

template <typename T>
const bool DataBase::TryGetRecordComponent(const Entity &record, T *&out) const
{
    static_assert(std::is_base_of_v<Components::IComponent, std::decay_t<T>>,
                  "T must derive from IComponent");

    std::weak_ptr<ECS::Stash<T>> wptrStash = m_dbWorld->GetStash<T>();

    if (wptrStash.expired())
    {
        return false;
    }

    std::shared_ptr<ECS::Stash<T>> ptrStash = wptrStash.lock();
    if (ptrStash->Has(record))
    {

        out = &ptrStash->Get(record);
        return true;
    }
    else
    {
        return false;
    }
}