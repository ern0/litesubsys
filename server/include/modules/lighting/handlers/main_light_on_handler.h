#pragma once

#include "event_handler.h"

namespace com_c
{
class IEvent;

namespace lighting_m
{   
class Power;

class MainLightOffHandler : IEventHandler
{
public:
    
    MainLightOffHandler( std::shared_ptr<Power> );
    void handle(std::shared_ptr<IEvent>) override;

private:
    
    std::shared_ptr<Power> mPower;
};

} // power_m
} // com_c