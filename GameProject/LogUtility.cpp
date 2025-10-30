#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING

#include "LogUtility.h"
#include "Components.h"
#include "DataBase.h"
#include "Filter.h"
#include "Stash.h"
#include "World.h"

#include <algorithm>
#include <fmt/color.h>
#include <fmt/core.h>

using namespace Utilities;

fmt::color getRarityColor(Rarity::Rarities rarity)
{
    switch (rarity)
    {
    case Rarity::COMMON:
        return fmt::color::white;
    case Rarity::UNCOMMON:
        return fmt::color::green;
    case Rarity::RARE:
        return fmt::color::blue;
    case Rarity::EPIC:
        return fmt::color::magenta;
    case Rarity::LEGENDARY:
        return fmt::color::gold;
    case Rarity::QUEST:
        return fmt::color::lime;
    default:
        return fmt::color::white;
    }
}

std::string create_header()
{
    return fmt::format("{:<3} {:<20} {:<25} {:>8} {:>8} {:>10}",
                       "N", "Name", "Description", "Damage", "Armor", "Cost");
}

std::string LogUtility::item_log_standart(std::shared_ptr<ECS::World> world, ECS::Entity &item_entity, int item_index)
{
    static std::string result;

    // Получаем сташи из мира
    auto nameStashWeak   = world->GetStash<Name>();
    auto descStashWeak   = world->GetStash<Description>();
    auto rarityStashWeak = world->GetStash<Rarity>();
    auto damageStashWeak = world->GetStash<Damage>();
    auto armorStashWeak  = world->GetStash<Armor>();
    auto costStashWeak   = world->GetStash<Cost>();

    auto nameStash   = nameStashWeak.lock();
    auto descStash   = descStashWeak.lock();
    auto rarityStash = rarityStashWeak.lock();
    auto damageStash = damageStashWeak.lock();
    auto armorStash  = armorStashWeak.lock();
    auto costStash   = costStashWeak.lock();

    // Определяем цвет редкости
    fmt::color rarity_color = fmt::color::white;
    if (rarityStash && rarityStash->Has(item_entity))
    {
        const Rarity &rarity = rarityStash->Get(item_entity);
        rarity_color         = getRarityColor(rarity.m_Value);
    }

    // Получаем данные из компонентов
    std::string name_str = "Unknown";
    if (nameStash && nameStash->Has(item_entity))
    {
        name_str = nameStash->Get(item_entity).m_Value;
        if (name_str.length() > 18)
            name_str = name_str.substr(0, 15) + "...";
    }

    std::string desc_str = "No description";
    if (descStash && descStash->Has(item_entity))
    {
        desc_str = descStash->Get(item_entity).m_Value;
        if (desc_str.length() > 23)
            desc_str = desc_str.substr(0, 20) + "...";
    }

    std::string damage_str = "0";
    if (damageStash && damageStash->Has(item_entity))
    {
        damage_str = std::to_string(damageStash->Get(item_entity).m_Value);
    }

    std::string armor_str = "0";
    if (armorStash && armorStash->Has(item_entity))
    {
        armor_str = std::to_string(armorStash->Get(item_entity).m_Value);
    }

    std::string cost_str = "-";
    if (costStash && costStash->Has(item_entity))
    {
        cost_str = fmt::format("{:.1f}", costStash->Get(item_entity).m_Value);
    }

    result = fmt::format(fmt::fg(rarity_color), "{:<3} {:<20} {:<25} {:>8} {:>8} {:>10}",
                         item_index, name_str, desc_str, damage_str, armor_str, cost_str);

    return result;
}

void LogUtility::print_items_table(std::shared_ptr<ECS::World>        world,
                                   const std::shared_ptr<ECS::Filter> itemsFilter,
                                   SortType                           sortType)
{
    std::vector<std::shared_ptr<ECS::Entity>> items(itemsFilter->begin(), itemsFilter->end());

    // Получаем сташи для сортировки
    auto rarityStashWeak = world->GetStash<Rarity>();
    auto costStashWeak   = world->GetStash<Cost>();

    auto rarityStash = rarityStashWeak.lock();
    auto costStash   = costStashWeak.lock();

    switch (sortType)
    {
    case SortType::BY_RARITY:
        if (rarityStash)
        {
            std::sort(items.begin(), items.end(),
                      [&rarityStash](const std::shared_ptr<ECS::Entity> &a, const std::shared_ptr<ECS::Entity> &b) -> bool
                      {
                          bool hasRarityA = rarityStash->Has(*a);
                          bool hasRarityB = rarityStash->Has(*b);

                          if (!hasRarityA && !hasRarityB)
                              return false;
                          if (!hasRarityA)
                              return false;
                          if (!hasRarityB)
                              return true;

                          int rarityValueA = static_cast<int>(rarityStash->Get(*a).m_Value);
                          int rarityValueB = static_cast<int>(rarityStash->Get(*b).m_Value);

                          return rarityValueA > rarityValueB;
                      });
        }
        break;

    case SortType::BY_PRICE_ASC:
        if (costStash)
        {
            std::sort(items.begin(), items.end(),
                      [&costStash](const std::shared_ptr<ECS::Entity> &a, const std::shared_ptr<ECS::Entity> &b) -> bool
                      {
                          bool hasCostA = costStash->Has(*a);
                          bool hasCostB = costStash->Has(*b);

                          if (!hasCostA && !hasCostB)
                              return false;
                          if (!hasCostA)
                              return false;
                          if (!hasCostB)
                              return true;

                          float costValueA = costStash->Get(*a).m_Value;
                          float costValueB = costStash->Get(*b).m_Value;

                          return costValueA < costValueB;
                      });
        }
        break;

    case SortType::BY_PRICE_DESC:
        if (costStash)
        {
            std::sort(items.begin(), items.end(),
                      [&costStash](const std::shared_ptr<ECS::Entity> &a, const std::shared_ptr<ECS::Entity> &b) -> bool
                      {
                          bool hasCostA = costStash->Has(*a);
                          bool hasCostB = costStash->Has(*b);

                          if (!hasCostA && !hasCostB)
                              return false;
                          if (!hasCostA)
                              return true;
                          if (!hasCostB)
                              return false;

                          float costValueA = costStash->Get(*a).m_Value;
                          float costValueB = costStash->Get(*b).m_Value;

                          return costValueA > costValueB;
                      });
        }
        break;

    case SortType::NONE:
    default:
        break;
    }

    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "{}\n", create_header());

    fmt::print(fg(fmt::color::gray), "{}\n",
               std::string(5 + 20 + 25 + 8 + 8 + 10 + 3, '-'));

    int index = 0;
    for (const auto &item : items)
    {
        ++index;
        fmt::print("{}\n", item_log_standart(world, *item, index));
    }
}