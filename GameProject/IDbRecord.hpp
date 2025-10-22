#pragma once

#include "DataBase.h"
#include "IDbRecord.h"
#include "Stash.h"
#include "World.h"

template <typename T>
void DB::IDbRecord::With(T component)
{
    static_assert(std::is_base_of_v<Components::IComponent, std::decay_t<T>>,
                  "T must derive from IComponent");

    if (!m_record.expired())
    {
        auto db = DB::DataBase::GetInstance();

        if (db.m_dbWorld)
        {
            std::weak_ptr<ECS::Stash<T>> weak_stash = db.m_dbWorld->GetStash<T>();

            if (auto stash = weak_stash.lock())
            {
                auto entity = m_record.lock();
                if (entity)
                {
                    stash->Add(*entity, std::move(component));
                }
            }
        }
    }
}