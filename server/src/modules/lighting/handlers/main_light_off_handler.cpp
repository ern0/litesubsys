#include "main_light_off_handler.h"
#include "main_light_off.h"
#include "lighting.h"

namespace com_c
{
namespace lighting_m
{

MainLightOffHandler::MainLightOffHandler()
{
    // empty
}

void MainLightOffHandler::handle(std::shared_ptr<IEvent> iEvent)
{
    auto wEvent = iEvent->interpretAs<MainLightOffEvent>();

    if(NULL != wEvent)
    {
        Lighting::getInstance()->setLighting(false);
        wEvent->process();
    }
    else
    {
        // pass;
    }
}

} // power_m
} // com_c