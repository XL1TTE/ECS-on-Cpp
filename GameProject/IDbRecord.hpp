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
        // Убедитесь, что m_dbWorld существует и GetStash<T>() работает
        if (DB::DataBase::GetInstance().m_dbWorld)
        {
            std::weak_ptr<ECS::Stash<T>> weak_stash = DB::DataBase::GetInstance().m_dbWorld->GetStash<T>();

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