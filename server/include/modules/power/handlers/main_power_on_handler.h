#pragma once

#include "event_handler.h"

namespace com_c
{
class IEvent;

namespace power_m
{   
class Power;

class MainPowerOnHandler : IEventHandler
{
public:
    
    MainPowerOnHandler();
    void handle(std::shared_ptr<IEvent>) override;
};

} // power_m
} // com_c