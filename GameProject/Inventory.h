#pragma once
#include <memory>
#include <string>
#include <vector>

namespace ECS
{
struct Entity;
class World;
struct Filter;
} // namespace ECS

class Inventory
{
  private:
    Inventory();

  public:
    static std::shared_ptr<Inventory> Create();

    bool AddItemByID(const std::string &itemID);
    bool AddItemByEntity(const ECS::Entity &entity);

    bool RemoveItemByEntity(const ECS::Entity &entity);
    bool RemoveItemByIndex(size_t index);
    bool RemoveItemByID(const std::string &id);

    void   ShowAllItems() const;
    size_t GetItemCount() const;

    std::shared_ptr<ECS::World> GetWorld() const
    {
        return m_world;
    }

    std::weak_ptr<ECS::Entity> FindItemByID(const std::string &itemID) const;

  private:
    std::shared_ptr<ECS::World> m_world;
    std::shared_ptr<ECS::World> m_dbWorld;

    std::weak_ptr<ECS::Filter> CreateItemsFilter() const;
};