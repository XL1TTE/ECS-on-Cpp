#include "Inventory.h"
#include "Components.h"
#include "ConsoleItemsAPI.h"
#include "DataBase.h"
#include "Filter.h"
#include "IDComponent.h"
#include "LogUtility.h"
#include "World.h"
#include <iostream>

Inventory::Inventory()
    : m_world(ECS::World::Create()), m_dbWorld(DataBase::GetInstance().m_dbWorld)
{
}

std::shared_ptr<Inventory> Inventory::Create()
{
    return std::shared_ptr<Inventory>(new Inventory()); // Need to create shared_ptr this way, because of private constructor.
}

bool Inventory::AddItemByID(const std::string &itemID)
{
    auto item = DataBase::GetInstance().TryGetRecordByID(itemID);

    if (!item.has_value())
    {
        std::cout << "Item with ID '" << itemID << "' not found in database" << std::endl;
        return false;
    }

    auto itemEntity = item.value().lock();
    if (!itemEntity)
    {
        std::cout << "Failed to lock entity for item '" << itemID << "'" << std::endl;
        return false;
    }

    auto newItem = m_dbWorld->CloneTo(*itemEntity, m_world);
    m_world->Commit();

    if (newItem.expired())
    {
        std::cout << "Failed to clone item '" << itemID << "' to inventory" << std::endl;
        return false;
    }

    std::cout << "Successfully added item '" << itemID << "' to inventory" << std::endl;
    return true;
}

bool Inventory::AddItemByEntity(const ECS::Entity &entity)
{
    try
    {
        auto newItem = m_dbWorld->CloneTo(entity, m_world);

        if (newItem.expired())
        {
            std::cout << "Failed to clone entity to inventory" << std::endl;
            return false;
        }

        auto nameStashWeak = m_dbWorld->GetStash<Name>();
        auto nameStash     = nameStashWeak.lock();

        if (nameStash && nameStash->Has(entity))
        {
            const Name &name = nameStash->Get(entity);
            std::cout << "Successfully added item '" << name.m_Value << "' to inventory" << std::endl;
        }
        else
        {
            std::cout << "Successfully added item to inventory" << std::endl;
        }

        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error adding item to inventory: " << e.what() << std::endl;
        return false;
    }
}

bool Inventory::RemoveItemByEntity(const ECS::Entity &entity)
{
    try
    {
        m_world->DisposeEntity(entity);
        std::cout << "Item removed from inventory" << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error removing item from inventory: " << e.what() << std::endl;
        return false;
    }
}

bool Inventory::RemoveItemByID(const std::string &id)
{
    auto item = FindItemByID(id);

    if (item.expired())
    {
        std::cout << "Item with ID '" << id << "' not found in inventory" << std::endl;
        return false;
    }

    auto itemEntity = item.lock();
    try
    {
        m_world->DisposeEntity(*itemEntity);
        m_world->Commit();
        std::cout << "Item '" << id << "' successfully removed from inventory" << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error removing item '" << id << "' from inventory: " << e.what() << std::endl;
        return false;
    }
}

bool Inventory::RemoveItemByIndex(size_t index)
{
    auto                                      filter = CreateItemsFilter().lock();
    std::vector<std::shared_ptr<ECS::Entity>> items(filter->begin(), filter->end());

    if (index >= items.size())
    {
        std::cout << "Invalid item index: " << index << std::endl;
        return false;
    }

    return RemoveItemByEntity(*items[index]);
}

void Inventory::ShowAllItems() const
{
    Utilities::ConsoleItemsAPI::ShowItems(m_world);
}

size_t Inventory::GetItemCount() const
{
    auto filter = CreateItemsFilter().lock();
    return std::distance(filter->begin(), filter->end());
}

std::weak_ptr<ECS::Entity> Inventory::FindItemByID(const std::string &itemID) const
{
    auto filter = CreateItemsFilter().lock();

    for (const auto &entity : *filter)
    {
        auto idStashWeak = m_world->GetStash<IDComponent>();
        auto idStash     = idStashWeak.lock();

        if (idStash && idStash->Has(*entity))
        {
            const IDComponent &id = idStash->Get(*entity);
            if (id.m_id == itemID)
            {
                return entity;
            }
        }
    }

    return std::weak_ptr<ECS::Entity>();
}

std::weak_ptr<ECS::Filter> Inventory::CreateItemsFilter() const
{
    return m_world->Filter()->Build();
}