#pragma once

#include <mutex>
#include <string>
#include <memory>

std::mutex g_mutex;

namespace com_c
{

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

    template< typename T>
    std::shared_ptr<T> interpretAs()
    {
        return std::dynamic_pointer_cast<std::shared_ptr<T> >(this);
    }
};

class NullEvent : public IEvent
{
    public:
    NullEvent( std::string iData) : IEvent(iData) {}
};

} // com_c
