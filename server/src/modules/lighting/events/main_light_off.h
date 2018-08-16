#pragma once

#include "event.h"

namespace com_c
{
namespace lighting_m
{   

class MainLightOffEvent : public IEvent
{
public:
    MainLightOffEvent()
    {
        // empty
    }
};

} // lighting_m
} // com_c