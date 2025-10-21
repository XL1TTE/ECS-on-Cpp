#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class IronSwordRecord : IDbRecord
{
  public:
    IronSwordRecord()
    {
        With<IDComponent>(IDComponent("weapon_iron-sword"));

        With<Item>(Item());

        With<Name>(Name("Iron Sword"));
        With<Description>(Description("Sword from iron. Looks sharp enought."));

        With<Rarity>(Rarity(Rarity::UNCOMMON));

        With<Damage>(Damage(10));
        With<Armor>(Armor(5));

        With<Cost>(Cost(100));
    }
};

} // namespace DB
