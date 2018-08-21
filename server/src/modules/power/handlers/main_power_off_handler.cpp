#include "main_power_off_handler.h"
#include "main_power_off.h"
#include "power.h"

namespace com_c
{
namespace power_m
{

MainPowerOffHandler::MainPowerOffHandler()
{
    // empty
}

void MainPowerOffHandler::handle(std::shared_ptr<IEvent> iEvent)
{
	auto wEvent = iEvent->interpretAs<MainPowerOffEvent>();

    if(NULL != wEvent)
    {
        Power::getInstance()->setPower(false);
        // todo: Erno kapcsolja le az aramot!
        wEvent->process();
    }
    else
    {
        // pass;
    }
}

} // power_m
} // com_c
