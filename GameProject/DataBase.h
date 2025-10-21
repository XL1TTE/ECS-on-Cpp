#pragma once

#include <memory>
#include <optional>
#include <string>

namespace ECS
{
class World;
struct Entity;
struct FilterBuilder;
} // namespace ECS

namespace DB
{

#define REGISTER_DB_RECORD(T) \
    static bool T##_registered = (DB::DataBase::GetInstance().RegisterRecordType<T>(), true);

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
    static DataBase &GetInstance()
    {
        static DataBase instance;
        return instance;
    }

    std::shared_ptr<ECS::FilterBuilder> Filter() const;

    template <typename T>
    void RegisterRecordType()
    {
        T tempInstance;
    }

    void                                             AddRecord(std::shared_ptr<ECS::Entity> entity);
    const std::optional<std::weak_ptr<ECS::Entity>> &TryGetRecordByID(const std::string &id) const;

    template <typename T>
    const bool TryGetRecordComponent(const ECS::Entity &record, T *&out) const;

  private:
    void resize(size_t requiredSize);
};

} // namespace DB

#include "DataBase.hpp"
