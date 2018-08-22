#pragma once

#include <mutex>
#include <string>
#include <memory>

//std::mutex g_mutex;

namespace com_c
{

class IEvent : public std::enable_shared_from_this<IEvent>
{
public:
    explicit IEvent(std::string iData);
    IEvent();
protected:

    bool mProcessed; ///< Flag to indicate if the event has been processed.
    std::string mData; ///< Pointer to the event data.

public:

    /// Thread-safe trigger of the mProcessed flag.
    virtual void process();

    bool isPorcessed() const;

    template< typename T>
    std::shared_ptr<T> interpretAs()
    {
        static_assert(std::is_base_of<IEvent, T>::value, "type parameter of this class must derive from IEvent");
        return std::dynamic_pointer_cast<T>(shared_from_this());
    }
};

class NullEvent : public IEvent
{
    public:
    NullEvent( std::string iData) : IEvent(iData) {}
    NullEvent() : IEvent() {}
};

} // com_c
