#pragma once

#include "event.h"


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