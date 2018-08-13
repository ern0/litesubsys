#pragma once

#include "event_handler.h"

namespace com_c
{
class IEvent;

namespace lighting_m
{   

class MainLightOnHandler : IEventHandler
{
public:
    
    MainLightOnHandler();
    void handle(std::shared_ptr<IEvent>) override;
};

} // power_m
} // com_c