#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class DragonChestPlateRecord : IDbRecord
{
  public:
    DragonChestPlateRecord()
    {
        With<IDComponent>(IDComponent("armor_dragon-armor"));

        With<Item>(Item());
        With<Wearable>(Wearable());

        With<Name>(Name("Dragon's Armor"));
        With<Description>(Description("Chest plate made from dragon's skin."));

        With<Armor>(Armor(15));
        With<Rarity>(Rarity(Rarity::EPIC));

        With<Cost>(Cost(5000));
    }
};
} // namespace DB
