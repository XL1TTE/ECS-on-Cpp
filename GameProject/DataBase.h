#pragma once

#include <memory>
#include <optional>
#include <string>

namespace ECS
{
class World;
struct Entity;
} // namespace ECS

namespace DB
{

class DataBase final
{
  public:
    DataBase();

  public:
    std::shared_ptr<ECS::World> m_dbWorld;

  private:
    size_t                                                         m_bufferSize = 0;
    size_t                                                         m_capacity   = 0;
    std::shared_ptr<std::optional<std::shared_ptr<ECS::Entity>>[]> m_records;

  public:
    void                                             AddRecord(std::shared_ptr<ECS::Entity> entity);
    const std::optional<std::weak_ptr<ECS::Entity>> &TryGetRecordByID(const size_t &&id_hash) const;

  private:
    void resize(size_t requiredSize);
};

} // namespace DB
