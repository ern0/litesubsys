#pragma once

#include "event.h"

namespace com_c
{
namespace power_m
{   

class MainPowerOnEvent : public IEvent
{
public:
    MainPowerOnEvent()
    {
        // empty
    }

    explicit MainPowerOnEvent( std::string iData) : IEvent(iData) 
    {
        // empty
    }
};

} // power_m
} // com_c