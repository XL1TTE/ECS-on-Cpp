#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class LeatherArmorRecord : public IDbRecord
{
  public:
    LeatherArmorRecord()
    {
        With<IDComponent>(IDComponent("armor_leather_armor"));
        With<Item>(Item());
        With<Name>(Name("Leather Armor"));
        With<Description>(Description("Light armor made from tanned animal hide."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Armor>(Armor(8));
        With<Cost>(Cost(50));
    }
};

class ChainmailRecord : public IDbRecord
{
  public:
    ChainmailRecord()
    {
        With<IDComponent>(IDComponent("armor_chainmail"));
        With<Item>(Item());
        With<Name>(Name("Chainmail"));
        With<Description>(Description("Flexible armor made of interlocking metal rings."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Armor>(Armor(15));
        With<Cost>(Cost(120));
    }
};

class PlateArmorRecord : public IDbRecord
{
  public:
    PlateArmorRecord()
    {
        With<IDComponent>(IDComponent("armor_plate"));
        With<Item>(Item());
        With<Name>(Name("Plate Armor"));
        With<Description>(Description("Heavy armor providing excellent protection."));
        With<Rarity>(Rarity(Rarity::RARE));
        With<Armor>(Armor(25));
        With<Cost>(Cost(400));
    }
};

class DragonScaleRecord : public IDbRecord
{
  public:
    DragonScaleRecord()
    {
        With<IDComponent>(IDComponent("armor_dragon-scale"));
        With<Item>(Item());
        With<Name>(Name("Dragon Scale Armor"));
        With<Description>(Description("Legendary armor crafted from dragon scales."));
        With<Rarity>(Rarity(Rarity::LEGENDARY));
        With<Armor>(Armor(40));
        With<Cost>(Cost(1500));
    }
};

class MageRobeRecord : public IDbRecord
{
  public:
    MageRobeRecord()
    {
        With<IDComponent>(IDComponent("armor_mage-robe"));
        With<Item>(Item());
        With<Name>(Name("Mage's Robe"));
        With<Description>(Description("Enchanted robe that enhances magical abilities."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Armor>(Armor(5));
        With<Cost>(Cost(200));
    }
};

class CloakRecord : public IDbRecord
{
  public:
    CloakRecord()
    {
        With<IDComponent>(IDComponent("armor_cloak"));
        With<Item>(Item());
        With<Name>(Name("Traveler's Cloak"));
        With<Description>(Description("Warm cloak for protection against the elements."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Armor>(Armor(3));
        With<Cost>(Cost(20));
    }
};

class ShieldRecord : public IDbRecord
{
  public:
    ShieldRecord()
    {
        With<IDComponent>(IDComponent("armor_shield"));
        With<Item>(Item());
        With<Name>(Name("Knight's Shield"));
        With<Description>(Description("Sturdy shield for blocking attacks."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Armor>(Armor(12));
        With<Damage>(Damage(2));
        With<Cost>(Cost(100));
    }
};

class HelmetRecord : public IDbRecord
{
  public:
    HelmetRecord()
    {
        With<IDComponent>(IDComponent("armor_helmet"));
        With<Item>(Item());
        With<Name>(Name("Iron Helmet"));
        With<Description>(Description("Protective headgear."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Armor>(Armor(6));
        With<Cost>(Cost(45));
    }
};

class BootsRecord : public IDbRecord
{
  public:
    BootsRecord()
    {
        With<IDComponent>(IDComponent("armor_boots"));
        With<Item>(Item());
        With<Name>(Name("Leather Boots"));
        With<Description>(Description("Comfortable boots for long journeys."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Armor>(Armor(4));
        With<Cost>(Cost(30));
    }
};

class GlovesRecord : public IDbRecord
{
  public:
    GlovesRecord()
    {
        With<IDComponent>(IDComponent("armor_gloves"));
        With<Item>(Item());
        With<Name>(Name("Gauntlets"));
        With<Description>(Description("Metal gloves for hand protection."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Armor>(Armor(5));
        With<Cost>(Cost(35));
    }
};

} // namespace DB