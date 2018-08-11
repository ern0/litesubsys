#include "lighting.h"
#include "power.h"
#include "event.h"
#include "event_handler.h"
#include "engine_power_on_handler.h"

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
    mPowerModule = Power::getInstance();
}

void Lighting::setLighting(bool iLighting)
{
    mLightingOn = iLighting;
}

} // lighting_m
} // com_c