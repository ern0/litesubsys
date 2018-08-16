#pragma once

#include "event.h"

namespace com_c
{
namespace power_m
{   

class MainPowerOffEvent : public IEvent
{
public:
    MainPowerOffEvent()
    {
        // empty
    }
};

} // power_m
} // com_c