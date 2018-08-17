#include "power.h"
#include "event.h"
#include "event_handler.h"
#include "main_power_on_handler.h"
#include "main_power_off_handler.h"

namespace com_c
{
namespace power_m
{


std::shared_ptr<Power> Power::getInstance()
{
    static std::shared_ptr<Power> wPower = std::shared_ptr<Power>(new Power());
    return wPower;

}

Power::Power()
{
    //mHandlers.push_back( std::make_unique<IEventHandler>(new MainPowerOnHandler()));
    //mHandlers.push_back( std::make_unique<IEventHandler>(new MainPowerOffHandler()));
}

void Power::setPower(bool iPower)
{
    mPowerOn = iPower;
}

bool Power::getPower() const
{
    return mPowerOn;
}

} // power_m
} // com_c
