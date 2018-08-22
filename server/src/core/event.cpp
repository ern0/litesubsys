#include "event.h"
#include "event_handler.h"

namespace com_c
{

IEvent::IEvent()
{
    // empty
}

IEvent::IEvent(std::string iData) : mData(iData) 
{
    // empty
}

void IEvent::process()
{
    //std::lock_guard<std::mutex> guard(g_mutex);
    mProcessed = true;
}

bool IEvent::isPorcessed() const
{
    return mProcessed;
}

} // com_c
