#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class SpectralKeyRecord : IDbRecord
{
  public:
    SpectralKeyRecord()
    {
        With<IDComponent>(IDComponent("quest-item_spectral-key"));

        With<Item>(Item());
        With<QuestItem>(QuestItem());

        With<Name>(Name("Spectral Key"));
        With<Description>(Description("A cold, translucent key that seems to flicker in and out of sight."));

        With<Rarity>(Rarity(Rarity::QUEST));

        With<Cost>(Cost(100));
    }
};

} // namespace DB
