#include "main_power_on_handler.h"
#include "main_power_on.h"
#include "power.h"

namespace com_c
{
namespace power_m
{

MainPowerOnHandler::MainPowerOnHandler( )
{
    // empty
}

void MainPowerOnHandler::handle(std::shared_ptr<IEvent> iEvent)
{
		/*
    auto wEvent = iEvent->interpretAs<MainPowerOnEvent>();

    if (NULL != wEvent)
    {
        Power::getInstance()->setPower(true);
        // todo: Erno kapcsolja be az aramot!
        wEvent->process();
    }
    else
    {
        // pass;
    }
    */
}

} // power_m
} // com_c
