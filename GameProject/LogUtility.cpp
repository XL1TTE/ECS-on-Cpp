#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING

#include "LogUtility.h"
#include "Components.h"
#include "DataBase.h"
#include "Entity.h"
#include "Filter.h"
#include "Stash.h"

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
    default:
        return fmt::color::white;
    }
}

std::string create_header()
{
    return fmt::format("{:<3} {:<20} {:<25} {:>8} {:>8} {:>10}",
                       "N", "Name", "Description", "Damage", "Armor", "Cost");
}

const std::string &LogUtility::item_log_standart(ECS::Entity &item_entity, int item_index)
{
    static std::string result;

    auto &db = DataBase::GetInstance();

    fmt::color rarity_color = fmt::color::white;
    if (Rarity *rarity = nullptr; db.TryGetRecordComponent<Rarity>(item_entity, rarity))
    {
        rarity_color = getRarityColor(rarity->m_Value);
    }

    Name        *item_name   = nullptr;
    Description *item_desc   = nullptr;
    Damage      *item_damage = nullptr;
    Armor       *item_armor  = nullptr;
    Cost        *item_cost   = nullptr;

    db.TryGetRecordComponent<Name>(item_entity, item_name);
    db.TryGetRecordComponent<Description>(item_entity, item_desc);
    db.TryGetRecordComponent<Damage>(item_entity, item_damage);
    db.TryGetRecordComponent<Armor>(item_entity, item_armor);
    db.TryGetRecordComponent<Cost>(item_entity, item_cost);

    std::string name_str = item_name ? item_name->m_Value : "Unknown";
    if (name_str.length() > 18)
        name_str = name_str.substr(0, 15) + "...";

    std::string desc_str = item_desc ? item_desc->m_Value : "No description";
    if (desc_str.length() > 23)
        desc_str = desc_str.substr(0, 20) + "...";

    std::string damage_str = item_damage ? std::to_string(item_damage->m_Value) : "0";
    std::string armor_str  = item_armor ? std::to_string(item_armor->m_Value) : "0";
    std::string cost_str   = item_cost ? fmt::format("{:.1f}", item_cost->m_Value) : "-";

    result = fmt::format(fmt::fg(rarity_color), "{:<3} {:<20} {:<25} {:>8} {:>8} {:>10}",
                         item_index, name_str, desc_str, damage_str, armor_str, cost_str);

    return result;
}

void LogUtility::print_items_table(const std::shared_ptr<ECS::Filter> itemsFilter)
{

    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold,
               "{}\n", create_header());

    fmt::print(fg(fmt::color::gray), "{}\n",
               std::string(5 + 20 + 25 + 8 + 8 + 10 + 3, '-'));

    int index = 0;
    for (const auto item : *itemsFilter)
    {
        ++index;
        fmt::print("{}\n", item_log_standart(*item, index));
    }
}