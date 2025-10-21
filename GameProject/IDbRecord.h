#pragma once
#include <memory>

namespace ECS
{
struct Entity;

template <typename T>
struct Stash;
} // namespace ECS

namespace DB
{
class DataBase;

class IDbRecord
{

  public:
    std::weak_ptr<ECS::Entity> m_record;

  protected:
    IDbRecord();

    template <typename T>
    void With(T component);
};

} // namespace DB

#include "IDbRecord.hpp"