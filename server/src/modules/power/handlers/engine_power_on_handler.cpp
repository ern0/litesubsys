#include "engine_power_on_handler.h"
#include "engine_power_on.h"
#include "power.h"

EnginePowerOnHandler::EnginePowerOnHandler( std::shared_ptr<Power> iPower ) 
: mPower(iPower)
{
    // empty
}

void EnginePowerOnHandler::handle(std::shared_ptr<IEvent> iEvent)
{
    auto wEvent = dynamic_cast<std::shared_ptr<EnginePowerOnEvent> >(iEvent);
    if(NULL != wEvent)
    {
        mPower->setPower(true);
        wEvent->processed();
    }
    else
    {
        // pass;
    }
}