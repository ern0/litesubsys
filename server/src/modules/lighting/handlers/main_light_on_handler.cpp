#include "main_light_on_handler.h"
#include "main_light_on.h"
#include "lighting.h"

namespace com_c
{
namespace lighting_m
{

MainLightOnHandler::MainLightOnHandler()
{
    // empty
}

void MainLightOnHandler::handle(std::shared_ptr<IEvent> iEvent)
{
    auto wEvent = iEvent->interpretAs<MainLightOnEvent>();

    if(NULL != wEvent)
    {
        Lighting::getInstance()->setLighting(true);
        // todo: Erno kapcsolja fel a lampat!
        wEvent->process();
    }
    else
    {
        // pass;
    }
}

} // lighting_m
} // com_c