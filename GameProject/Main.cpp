#pragma once

#include "Components.h"
#include "DataBase.h"
#include "Entity.h"
#include "Filter.h"
#include "IDComponent.h"
#include "LogUtility.h"
#include "Stash.h"
#include "World.h"
#include <memory>
#include <string>

int main()
{

    auto db = DB::DataBase::GetInstance();

    auto itemsFilter = db.Filter()
                           ->With<Item>()
                           .Build();

    Utilities::LogUtility::print_items_table(itemsFilter.lock());
}