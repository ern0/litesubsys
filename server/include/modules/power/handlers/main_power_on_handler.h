#pragma once

#include "event_handler.h"

class IEvent;
class Power;

class MainPowerOnHandler : IEventHandler
{
public:
    
    MainPowerOnHandler( std::shared_ptr<Power> );
    void handle(std::shared_ptr<IEvent>) override;

private:
    
    std::shared_ptr<Power> mPower;
};