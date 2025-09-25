#pragma once

#include "DataBase.h"
#include "Entity.h"
#include "Filter.h"
#include "IDComponent.h"
#include "World.h"
#include <memory>
#include <string>

int main()
{

    auto world = World::Create();
    {
        auto entity1 = world->CreateEntity();

        auto ids = world->GetStash<IDComponent>();

        ids.lock()->Add(*entity1.lock(), IDComponent(std::hash<std::string>{}("testFirstID")));

        auto filter = world->Filter()
                          ->With<IDComponent>()
                          .Build();

        for (const auto &entity : *filter.lock())
        {
            std::cout << "Entity ID: " << entity->m_id << std::endl;
        }

        auto filter2 = world->Filter()
                           ->With<IDComponent>()
                           .Build();

        for (const auto &entity : *filter2.lock())
        {
            std::cout << "Entity ID: " << entity->m_id << std::endl;
        }

        world->DisposeFilter(filter);

        world->Commit();

        std::cout << "END \n";
    }
}