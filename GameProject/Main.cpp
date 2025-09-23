#pragma once

#include "DataBase.h"
#include <memory>
#include "IDComponent.h"

int main() {

    auto db = std::make_shared<DataBase>();
    {
        auto entity = std::make_shared<Entity>();

        // Вариант 1: создание на месте
        //entity->AddComponent(IDComponent(1));  // без new!

        // Вариант 2: через shared_ptr
        auto idComp = std::make_shared<IDComponent>(2);
        entity->AddComponent(idComp);

        db->AddRecord(entity);
    }

    auto foundEntity = db->GetRecordById(2);
    if (foundEntity != nullptr) {
        std::cout << foundEntity->GetComponent<IDComponent>()->getId() << std::endl;
    }
}