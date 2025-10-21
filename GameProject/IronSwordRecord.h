#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class IronSwordRecord : IDbRecord
{
  public:
    IronSwordRecord()
    {
        With<IDComponent>(IDComponent("IronSword"));
        With<Damage>(Damage(10));
    }
};

} // namespace DB
