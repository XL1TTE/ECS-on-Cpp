#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class DeveloperSwordRecord : IDbRecord
{
  public:
    DeveloperSwordRecord()
    {
        With<IDComponent>(IDComponent("weapon_dev-sword"));

        With<Item>(Item());
        With<HiddenItem>(HiddenItem());

        With<Name>(Name("Developer's Sword"));
        With<Description>(Description("One punch sword."));

        With<Rarity>(Rarity(Rarity::LEGENDARY));

        With<Damage>(Damage(999));
    }
};
} // namespace DB
