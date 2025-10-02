#pragma once

#include "DataBase.h"
#include "Entity.h"
#include "IDComponent.h"
#include "Stash.h"
#include "World.h"
#include <string>

using namespace DB;

DataBase::DataBase()
    : m_capacity(16), m_bufferSize(16)
{
    m_dbWorld = ECS::World::Create();

    m_records = std::shared_ptr<std::optional<std::shared_ptr<ECS::Entity>>[]>(
        new std::optional<std::shared_ptr<ECS::Entity>>[m_capacity]);
}

const std::optional<std::weak_ptr<ECS::Entity>> &DataBase::TryGetRecordByID(const size_t &&id_hash) const
{
    auto idsPtr = m_dbWorld->GetStash<Components::IDComponent>();

    for (size_t i = 0; i < m_bufferSize; ++i)
    {
        auto entityWeakPtr = m_records[i];
        if (entityWeakPtr.has_value() == false)
        {
            continue;
        }

        if (entityWeakPtr.value() == nullptr)
        {
            continue;
        }

        auto ids = idsPtr.lock();
        if (ids->Has(*entityWeakPtr.value()) == false)
        {
            continue;
        }

        if (ids->Get(*entityWeakPtr.value()).m_id == id_hash)
        {
            return std::weak_ptr(entityWeakPtr.value());
        }
    }
    return std::nullopt;
}

void DataBase::AddRecord(std::shared_ptr<ECS::Entity> entity)
{
    bool emplaced = false;
    for (int i = 0; i < m_bufferSize; ++i)
    {
        if (m_records[i].has_value() == false)
        {
            m_records[i].emplace(entity);
            emplaced = true;
            break;
        }
    }
    if (emplaced == false)
    {
        resize(m_bufferSize + 1);
        AddRecord(entity);
    }
}
void DataBase::resize(size_t requiredSize)
{
    if (requiredSize <= m_bufferSize)
    {
        m_bufferSize = requiredSize;
        return;
    }
    size_t newCapacity  = m_capacity * 2;
    auto   newBufferPtr = std::shared_ptr<std::optional<std::shared_ptr<ECS::Entity>>[]>(new std::optional<std::shared_ptr<ECS::Entity>>[newCapacity]);

    for (size_t i = 0; i < m_bufferSize; ++i)
    {
        newBufferPtr[i] = std::move(m_records[i]);
    }

    m_records    = std::move(newBufferPtr);
    m_bufferSize = requiredSize;
    m_capacity   = newCapacity;
}
