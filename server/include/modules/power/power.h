#pragma once

#include <vector>
#include <memory> // smart pointres

#include "listener.h"

class Power : IListener
{
public:
    std::shared_ptr<Power> getInstance();
    void setPower(bool iPower);
    bool getPower() const;

private:
    Power();
    bool mPowerOn;
    std::shared_ptr<Power> mInstance;
};