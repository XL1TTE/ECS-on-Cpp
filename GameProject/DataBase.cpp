#pragma once

#include "DataBase.h"
#include "Entity.h"
#include "IDComponent.h"
#include <memory>

using namespace ECS;

void DataBase::AddRecord(std::shared_ptr<Entity> entity)
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
