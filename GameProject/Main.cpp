#pragma once

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

    auto bd = DB::DataBase();

    auto world = World::Create();
    {

        auto entity1 = bd.m_dbWorld->CreateEntity();

        auto ids = bd.m_dbWorld->GetStash<IDComponent>();

        ids.lock()->Add(*entity1.lock(), IDComponent("testFirstID"));

        bd.AddRecord(entity1.lock());

        auto filter = world->Filter()
                          ->With<IDComponent>()
                          .Build();

        // for (const auto &entity : *filter.lock())
        //{
        //     std::cout << "Entity ID: " << entity->m_id << std::endl;
        // }

        auto record = bd.TryGetRecordByID("testFirstID");

        if (record.has_value())
        {
            std::cout << record.value().lock()->m_id << std::endl;
        }

        IDComponent *id = nullptr;
        if (bd.TryGetRecordComponent<IDComponent>(*record.value().lock(), id))
        {
            std::cout << id->m_id << std::endl;
            id->m_id = "testID";
        }

        record = bd.TryGetRecordByID("testID");
        if (bd.TryGetRecordComponent<IDComponent>(*record.value().lock(), id))
        {
            std::cout << id->m_id << std::endl;
        }

        world->DisposeFilter(filter);

        world->Commit();

        std::cout << "END \n";
    }
}