#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class HealthRingRecord : public IDbRecord
{
  public:
    HealthRingRecord()
    {
        With<IDComponent>(IDComponent("jewellery_health-ring"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Ring of Health"));
        With<Description>(Description("Ring that slowly regenerates wearer's health."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Cost>(Cost(150));
    }
};

class ManaAmuletRecord : public IDbRecord
{
  public:
    ManaAmuletRecord()
    {
        With<IDComponent>(IDComponent("jewellery_mana-amulet"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Amulet of Mana"));
        With<Description>(Description("Increases magical power and mana regeneration."));
        With<Rarity>(Rarity(Rarity::RARE));
        With<Cost>(Cost(300));
    }
};

class StrengthBraceletRecord : public IDbRecord
{
  public:
    StrengthBraceletRecord()
    {
        With<IDComponent>(IDComponent("jewellery_strength-bracelet"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Bracelet of Strength"));
        With<Description>(Description("Grants enhanced physical power to the wearer."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Cost>(Cost(180));
    }
};

class InvisibilityCloakRecord : public IDbRecord
{
  public:
    InvisibilityCloakRecord()
    {
        With<IDComponent>(IDComponent("jewellery_invisibility-cloak"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Cloak of Invisibility"));
        With<Description>(Description("Mythical cloak that renders the wearer invisible."));
        With<Rarity>(Rarity(Rarity::LEGENDARY));
        With<Cost>(Cost(2000));
    }
};

class WisdomNecklaceRecord : public IDbRecord
{
  public:
    WisdomNecklaceRecord()
    {
        With<IDComponent>(IDComponent("jewellery_wisdom-necklace"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Necklace of Wisdom"));
        With<Description>(Description("Enhances intelligence and magical knowledge."));
        With<Rarity>(Rarity(Rarity::EPIC));
        With<Cost>(Cost(600));
    }
};

class SpeedEarringRecord : public IDbRecord
{
  public:
    SpeedEarringRecord()
    {
        With<IDComponent>(IDComponent("jewellery_speed-earring"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Earring of Speed"));
        With<Description>(Description("Increases movement and attack speed."));
        With<Rarity>(Rarity(Rarity::RARE));
        With<Cost>(Cost(250));
    }
};

class FireResistanceRingRecord : public IDbRecord
{
  public:
    FireResistanceRingRecord()
    {
        With<IDComponent>(IDComponent("jewellery_fire-resistance-ring"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Ring of Fire Resistance"));
        With<Description>(Description("Protects against fire-based attacks."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Cost>(Cost(220));
    }
};

class LuckPendantRecord : public IDbRecord
{
  public:
    LuckPendantRecord()
    {
        With<IDComponent>(IDComponent("jewellery_luck-pendant"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Pendant of Luck"));
        With<Description>(Description("Slightly increases chance of favorable outcomes."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Cost>(Cost(80));
    }
};

class RoyalCrownRecord : public IDbRecord
{
  public:
    RoyalCrownRecord()
    {
        With<IDComponent>(IDComponent("jewellery_royal-crown"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Royal Crown"));
        With<Description>(Description("Ornate crown worn by kings and queens."));
        With<Rarity>(Rarity(Rarity::EPIC));
        With<Damage>(Damage(10));
        With<Cost>(Cost(800));
    }
};

class MagicBangleRecord : public IDbRecord
{
  public:
    MagicBangleRecord()
    {
        With<IDComponent>(IDComponent("jewellery_magic-bangle"));
        With<Item>(Item());
        With<Jewellery>(Jewellery());
        With<Name>(Name("Magic Bangle"));
        With<Description>(Description("Ancient bangle with unknown magical properties."));
        With<Rarity>(Rarity(Rarity::RARE));
        With<Cost>(Cost(350));
    }
};

} // namespace DB