#pragma once

#include "Components.h"
#include "IDComponent.h"
#include "IDbRecord.h"

namespace DB
{

using namespace Components;

class DeveloperSwordRecord : IDbRecord
{
  public:
    DeveloperSwordRecord()
    {
        With<IDComponent>(IDComponent("DeveloperSword"));
        With<Damage>(Damage(999));
    }
};
} // namespace DB
