#include "lighting.h"
#include "power.h"
#include "event.h"
#include "event_handler.h"

//<handlers
#include "main_light_off_handler.h"
#include "main_light_on_handler.h"

namespace com_c
{

using power_m::Power;

namespace lighting_m
{

std::shared_ptr<Lighting> Lighting::getInstance()
{
    static std::shared_ptr<Lighting> wLighting = std::shared_ptr<Lighting>(new Lighting());
    return wLighting;

}

Lighting::Lighting() : mLightingOn(false)
{
    mHandlers.push_back( std::unique_ptr<IEventHandler>(new MainLightOnHandler()));
    mHandlers.push_back( std::unique_ptr<IEventHandler>(new MainLightOffHandler()));
}

void Lighting::setLighting(bool iLighting)
{
    mLightingOn = iLighting;
}

} // lighting_m
} // com_c