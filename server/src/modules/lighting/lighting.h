#pragma once

#include <vector>
#include <memory> // smart pointres

#include "listener.h"

namespace com_c
{

namespace power_m 
{
    class Power; //< Forward declaring com_c::power_m::Power class.
} // power_m

namespace lighting_m
{

class Lighting : IListener
{
public:

    static std::shared_ptr<Lighting> getInstance();
    
    void setLighting(bool iLighting);

    // delete copy and move constructors and assign operators
    Lighting(Lighting const&) = delete;             // Copy construct
    Lighting(Lighting&&) = delete;                  // Move construct
    Lighting& operator=(Lighting const&) = delete;  // Copy assign
    Lighting& operator=(Lighting &&) = delete;      // Move assign
private:

    Lighting();

    bool mLightingOn;

    // Dependency modules
    std::shared_ptr<power_m::Power> mPowerModule;
};


} // lighting_m
} // com_c