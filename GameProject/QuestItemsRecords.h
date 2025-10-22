#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class AncientScrollRecord : public IDbRecord
{
  public:
    AncientScrollRecord()
    {
        With<IDComponent>(IDComponent("quest_ancient-scroll"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Ancient Scroll"));
        With<Description>(Description("Yellowed scroll with forgotten writings."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(1)); // Quest items often have low/no value
    }
};

class LostKeyRecord : public IDbRecord
{
  public:
    LostKeyRecord()
    {
        With<IDComponent>(IDComponent("quest_lost-key"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Rusty Key"));
        With<Description>(Description("Old key that might unlock something important."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(5));
    }
};

class DragonEggRecord : public IDbRecord
{
  public:
    DragonEggRecord()
    {
        With<IDComponent>(IDComponent("quest_dragon-egg"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Dragon Egg"));
        With<Description>(Description("Rare dragon egg, warm to the touch."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(5000));
    }
};

class MysteriousOrbRecord : public IDbRecord
{
  public:
    MysteriousOrbRecord()
    {
        With<IDComponent>(IDComponent("quest_mysterious-orb"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Mysterious Orb"));
        With<Description>(Description("Glowing orb that pulses with unknown energy."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(100));
    }
};

class HerbSackRecord : public IDbRecord
{
  public:
    HerbSackRecord()
    {
        With<IDComponent>(IDComponent("quest_herb-sack"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Herbalist's Sack"));
        With<Description>(Description("Collection of rare medicinal herbs."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(50));
    }
};

class BlacksmithPackageRecord : public IDbRecord
{
  public:
    BlacksmithPackageRecord()
    {
        With<IDComponent>(IDComponent("quest_blacksmith-package"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Blacksmith's Package"));
        With<Description>(Description("Heavy package containing special tools."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(30));
    }
};

class CrystalShardRecord : public IDbRecord
{
  public:
    CrystalShardRecord()
    {
        With<IDComponent>(IDComponent("quest_crystal-shard"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Crystal Shard"));
        With<Description>(Description("Shard from a larger magical crystal."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(75));
    }
};

class LoveLetterRecord : public IDbRecord
{
  public:
    LoveLetterRecord()
    {
        With<IDComponent>(IDComponent("quest_love-letter"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Sealed Letter"));
        With<Description>(Description("Personal letter, better not read it."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(2));
    }
};

class TreasureMapRecord : public IDbRecord
{
  public:
    TreasureMapRecord()
    {
        With<IDComponent>(IDComponent("quest_treasure-map"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Treasure Map"));
        With<Description>(Description("Map showing location of hidden treasure."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(60));
    }
};

class ArtifactPieceRecord : public IDbRecord
{
  public:
    ArtifactPieceRecord()
    {
        With<IDComponent>(IDComponent("quest_artifact-piece"));
        With<Item>(Item());
        With<QuestItem>(QuestItem());
        With<Name>(Name("Ancient Artifact Piece"));
        With<Description>(Description("Fragment of a powerful ancient artifact."));
        With<Rarity>(Rarity(Rarity::QUEST));
        With<Cost>(Cost(200));
    }
};

} // namespace DB