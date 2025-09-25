#pragma once

#include "Entity.h"
#include <memory>

using namespace ECS;

class DataBase final
{
  public:
    DataBase() = default;

  private:
    static const size_t     m_bufferSize            = 64;
    std::shared_ptr<Entity> m_records[m_bufferSize] = {nullptr};

  public:
    void AddRecord(std::shared_ptr<Entity> entity);
};
