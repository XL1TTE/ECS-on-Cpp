#pragma once

#include <memory>
#include <string>

namespace ECS
{
struct Entity;
struct Filter;
} // namespace ECS

namespace Utilities
{

static class LogUtility
{
  public:
    static const std::string &item_log_standart(ECS::Entity &item_entity, int item_index);
    static void               print_items_table(const std::shared_ptr<ECS::Filter> itemsFilter);
};
} // namespace Utilities
