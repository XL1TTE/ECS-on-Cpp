#pragma once

#include "DataBase.h"
#include "IDComponent.h"
#include "World.h"
#include <memory>
#include <string>

int main()
{

    auto world = std::make_shared<ECS::World>();
    {
        auto entity1 = world->CreateEntity();
        auto entity2 = world->CreateEntity();

        std::cout << entity1.lock()->m_id << std::endl;
        std::cout << entity2.lock()->m_id << std::endl;

        world->DisposeEntity(*entity1.lock());

        auto ids = world->GetStash<IDComponent>();

        ids.lock()->Add(*entity1.lock(), IDComponent(std::hash<std::string>{}("testFirstID")));

        std::cout << ids.lock()->Get(*entity1.lock()).getId() << std::endl;

        ids.lock()->Get(*entity1.lock()).setId(3);

        std::cout << ids.lock()->Get(*entity1.lock()).getId() << std::endl;
    }
}