#include "power.h"
#include "event.h"
#include "event_handler.h"
#include "engine_power_on_handler.h"

std::shared_ptr<Power> Power::getInstance()
{
    if(!mInstance)
    {
        mInstance =  std::shared_ptr<Power>(new Power());
    }
    return mInstance;

}

Power::Power() : mInstance(nullptr)
{
    auto wThis = std::make_shared<Power>(this);
    auto wEnginePowerOnHandler = std::make_unique<IEventHandler>(new EnginePowerOnHandler(wThis));
    mHandlers.push_back(wEnginePowerOnHandler);
}

void Power::setPower(bool iPower)
{
    mPowerOn = iPower;
}

bool Power::getPower() const
{
    return mPowerOn;
}