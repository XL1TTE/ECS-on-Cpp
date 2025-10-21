#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"
#include <string>

namespace DB
{

using namespace Components;

class WoodenSwordRecord : IDbRecord
{
  public:
    WoodenSwordRecord()
    {
        With<IDComponent>(IDComponent("weapon_wooden-sword"));

        With<Item>(Item());

        With<Name>(Name("Wooden Sword"));
        With<Description>(Description("Sword from wood. Good for practice."));

        With<Rarity>(Rarity(Rarity::COMMON));

        With<Damage>(Damage(1));

        With<Cost>(Cost(5));
    }
};

} // namespace DB
