#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class WoodenSwordRecord : public IDbRecord
{
  public:
    WoodenSwordRecord()
    {
        With<IDComponent>(IDComponent("weapon_wooden-sword"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Wooden Sword"));
        With<Description>(Description("Basic training sword made of oak wood."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Damage>(Damage(5));
        With<Cost>(Cost(25));
    }
};

class SteelSwordRecord : public IDbRecord
{
  public:
    SteelSwordRecord()
    {
        With<IDComponent>(IDComponent("weapon_steel-sword"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Steel Sword"));
        With<Description>(Description("Reliable sword forged from hardened steel."));
        With<Rarity>(Rarity(Rarity::RARE));
        With<Damage>(Damage(15));
        With<Cost>(Cost(200));
    }
};

class DragonSlayerRecord : public IDbRecord
{
  public:
    DragonSlayerRecord()
    {
        With<IDComponent>(IDComponent("weapon_dragon-slayer"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Dragon Slayer"));
        With<Description>(Description("Legendary sword imbued with dragon's essence."));
        With<Rarity>(Rarity(Rarity::LEGENDARY));
        With<Damage>(Damage(35));
        With<Cost>(Cost(1000));
    }
};

class HunterBowRecord : public IDbRecord
{
  public:
    HunterBowRecord()
    {
        With<IDComponent>(IDComponent("weapon_hunter-bow"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Hunter's Bow"));
        With<Description>(Description("Well-crafted bow used by experienced hunters."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Damage>(Damage(12));
        With<Cost>(Cost(150));
    }
};

class FireStaffRecord : public IDbRecord
{
  public:
    FireStaffRecord()
    {
        With<IDComponent>(IDComponent("weapon_fire-staff"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Staff of Fire"));
        With<Description>(Description("Ancient staff channeling the power of flames."));
        With<Rarity>(Rarity(Rarity::EPIC));
        With<Damage>(Damage(25));
        With<Cost>(Cost(500));
    }
};

class PoisonDaggerRecord : public IDbRecord
{
  public:
    PoisonDaggerRecord()
    {
        With<IDComponent>(IDComponent("weapon_poison-dagger"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Poisoned Dagger"));
        With<Description>(Description("Concealed blade coated with deadly toxin."));
        With<Rarity>(Rarity(Rarity::RARE));
        With<Damage>(Damage(18));
        With<Cost>(Cost(300));
    }
};

class WarAxeRecord : public IDbRecord
{
  public:
    WarAxeRecord()
    {
        With<IDComponent>(IDComponent("weapon_war-axe"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Heavy War Axe"));
        With<Description>(Description("Massive axe capable of cleaving through armor."));
        With<Rarity>(Rarity(Rarity::UNCOMMON));
        With<Damage>(Damage(22));
        With<Cost>(Cost(180));
    }
};

class MagicWandRecord : public IDbRecord
{
  public:
    MagicWandRecord()
    {
        With<IDComponent>(IDComponent("weapon_magic-wand"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Apprentice's Wand"));
        With<Description>(Description("Simple wand for beginner spellcasters."));
        With<Rarity>(Rarity(Rarity::COMMON));
        With<Damage>(Damage(8));
        With<Cost>(Cost(75));
    }
};

class CrossbowRecord : public IDbRecord
{
  public:
    CrossbowRecord()
    {
        With<IDComponent>(IDComponent("weapon_crossbow"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Heavy Crossbow"));
        With<Description>(Description("Precise crossbow with excellent range."));
        With<Rarity>(Rarity(Rarity::RARE));
        With<Damage>(Damage(20));
        With<Cost>(Cost(350));
    }
};

class LightningSpearRecord : public IDbRecord
{
  public:
    LightningSpearRecord()
    {
        With<IDComponent>(IDComponent("weapon_lightning-spear"));
        With<Item>(Item());
        With<Weapon>(Weapon());
        With<Name>(Name("Lightning Spear"));
        With<Description>(Description("Spear that crackles with electrical energy."));
        With<Rarity>(Rarity(Rarity::EPIC));
        With<Damage>(Damage(28));
        With<Cost>(Cost(600));
    }
};

} // namespace DB