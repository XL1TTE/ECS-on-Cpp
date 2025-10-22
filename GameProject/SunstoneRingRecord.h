#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class SunstoneRingRecord : IDbRecord
{
  public:
    SunstoneRingRecord()
    {
        With<IDComponent>(IDComponent("jewellery_sunstone-ring"));

        With<Item>(Item());
        With<Jewellery>(Jewellery());

        With<Name>(Name("Sunstone Ring"));
        With<Description>(Description("A simple bronze band holding a warm, orange gem that pulses with light."));

        With<Rarity>(Rarity(Rarity::RARE));

        With<Cost>(Cost(0));
    }
};

} // namespace DB
