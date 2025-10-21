#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"
#include <string>

namespace DB
{

using namespace Components;

class WoodenSwordRecord : IDbRecord
{
  public:
    WoodenSwordRecord()
    {
        With<IDComponent>(IDComponent("WoodenSword"));
        With<Damage>(Damage(5));
    }
};

} // namespace DB
