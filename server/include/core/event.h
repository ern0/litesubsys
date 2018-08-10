#pragma once

#include <mutex>
#include <string>

std::mutex g_mutex;

class IEvent
{
public:
    IEvent(std::string iData) : mData(iData) {}
    IEvent(){}
protected:
    
    bool mProcessed; ///< Flag to indicate if the event has been processed.
    std::string mData; ///< Pointer to the event data.

public:
    
    /// Thread-safe trigger of the mProcessed flag.
    void process();

    bool isPorcessed() const;
};

class NullEvent : public IEvent
{
    public:
    NullEvent( std::string iData) : IEvent(iData) {}
}