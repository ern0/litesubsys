#pragma once

#include "event_handler.h"

namespace com_c
{
class IEvent;

namespace power_m
{   

class MainPowerOffHandler : public IEventHandler
{
public:
    
    MainPowerOffHandler();
    void handle(std::shared_ptr<IEvent>) override;
};

} // power_m
} // com_c