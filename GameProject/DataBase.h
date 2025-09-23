#pragma once

#include "Entity.h"
#include "IDComponent.h"
#include <memory>

class DataBase final
{
  public:
    DataBase() = default;

  private:
    static const size_t     m_bufferSize            = 64;
    std::shared_ptr<Entity> m_records[m_bufferSize] = {nullptr};

  public:
    void AddRecord(std::shared_ptr<Entity> entity)
    {
        for (int i = 0; i < m_bufferSize; ++i)
        {
            if (m_records[i] == nullptr)
            {
                m_records[i] = entity;
                break;
            }
        }
    }

    std::shared_ptr<Entity> GetRecordById(long id) const
    {
        for (auto &rec : m_records)
        {
            if (rec == nullptr)
            {
                continue;
            }
            std::shared_ptr<IDComponent> id_ptr = rec->GetComponent<IDComponent>();
            if (id_ptr != nullptr)
            {
                if (id_ptr->getId() == id)
                {
                    return rec;
                }
            }
        }
        throw std::exception("Entity with id: $id was not found!", id);
    }
};
