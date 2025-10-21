#pragma once

#include "Components.h"
#include "DataBase.h"
#include "Entity.h"
#include "Filter.h"
#include "IDComponent.h"
#include "Stash.h"
#include "World.h"
#include <memory>
#include <string>

int main()
{

    auto db = DB::DataBase::GetInstance();

    auto dbFilter = db.Filter()->With<IDComponent>().Build();

    for (auto entity : *dbFilter.lock())
    {
        IDComponent *id;
        Damage      *damage;
        if (db.TryGetRecordComponent<IDComponent>(*entity, id))
        {
            if (db.TryGetRecordComponent<Damage>(*entity, damage))
                std::cout << id->m_id << " have " << damage->m_Value << " damage." << std::endl;
        }
    }
}