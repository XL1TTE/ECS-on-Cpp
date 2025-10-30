#pragma once

#include "ConsoleItemsAPI.h"
#include "IDComponent.h"
#include "Inventory.h"
#include "LogUtility.h"
#include "World.h"
#include <chrono>
#include <string>
#include <thread>

using namespace Utilities;

static void WaitForSeconds(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void ScenarioStart()
{
    auto DB = DataBase::GetInstance();

    auto inventory1 = Inventory::Create();
    inventory1->AddItemByID("weapon_crossbow");

    LogUtility::ShowCenteredMessage("Here is all items awaible in the game.");

    WaitForSeconds(4);

    LogUtility::ShowCenteredMessage("You can sort items by categories and other options.");

    WaitForSeconds(4);

    Utilities::ConsoleItemsAPI::ShowItems(DataBase::GetInstance().m_dbWorld);

    LogUtility::ShowCenteredMessage("Now you will see player's inventory.");

    WaitForSeconds(4);

    inventory1->ShowAllItems();

    LogUtility::ShowCenteredMessage("Now we will add all quest items in the game to the inventory.");

    WaitForSeconds(4);

    auto         questItems = DB.Filter()->With<Item>().With<QuestItem>().Build();
    IDComponent *id;
    for (auto item : *questItems.lock())
    {
        if (!DB.TryGetRecordComponent<IDComponent>(*item, id))
        {
            continue;
        }
        inventory1->AddItemByID(id->m_id);
    }

    inventory1->ShowAllItems();

    LogUtility::ShowCenteredMessage("We can also remove any item eather by id or Entity.");
    WaitForSeconds(4);
    LogUtility::ShowCenteredMessage("Let's remove crossbow, that player had at the beggining.");
    WaitForSeconds(4);

    inventory1->RemoveItemByID("weapon_crossbow");
    inventory1->ShowAllItems();
}

int main()
{
    ScenarioStart();
}