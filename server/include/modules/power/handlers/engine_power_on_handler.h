#pragma once

#include "event_handler.h"

class IEvent;
class Power;

class EnginePowerOnHandler : IEventHandler
{
public:
    
    EnginePowerOnHandler( std::shared_ptr<Power> );
    void handle(std::shared_ptr<IEvent>) override;

private:
    
    std::shared_ptr<Power> mPower;
};