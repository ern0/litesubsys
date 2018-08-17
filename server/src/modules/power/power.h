#pragma once

#include <vector>
#include <memory> // smart pointres

#include "listener.h"

namespace com_c
{
namespace power_m
{

class Power //: public IListener
{

public:
    static std::shared_ptr<Power> getInstance();
    void setPower(bool iPower);
    bool getPower() const;

    // delete copy and move constructors and assign operators
    Power(Power const&) = delete;             // Copy construct
    Power(Power&&) = delete;                  // Move construct
    Power& operator=(Power const&) = delete;  // Copy assign
    Power& operator=(Power &&) = delete;      // Move assign

private:
    Power();
    bool mPowerOn;
};

} // power_m
} // com_c
