#pragma once

#include <vector>
#include <memory> // smart pointres

#include "listener.h"

class Power;

class Lighting : IListener
{
public:

    Lighting();

    void setLighting(bool iLighting);
    bool getLighting() const;

private:

    bool mLightingOn;

    // Dependency modules
    const std::shared_ptr<Power> mPowerModule;
};